#include "AssistantCore.h"
#include "utils/UIUtils.h"
#include <termcolor/termcolor.hpp>
#include <iostream>
#include <sstream>

using namespace std;

AssistantCore::AssistantCore() {
    interaction.loadModel(modelManager.getCurrentModel());
    interaction.addChatMessage("You are a helpful assistant.", "system");
}

AssistantCore::~AssistantCore() {}

void AssistantCore::processQuery(const string &input, std::function<void(const std::string&)> onToken) {
    if (input == "/quit" || input == "quit") {
        onToken("quit");
        return;
    }

    std::string processedInput = input;
    std::string fileContents;

    // Extract file references and append content
    std::vector<std::string> fileReferences = parser.extractFileReferences(input);
    for (const std::string& filePath : fileReferences) {
        std::string content = UIUtils::readFileContent(filePath);
        if (content.rfind("Error:", 0) == 0) { // Check if readFileContent returned an error
            onToken(content + "\n");
            return; // Stop processing if file error
        }
        fileContents += "\n--- File: " + filePath + " ---\n" + content + "\n--- End of File ---\n";
        // Remove the @filepath from the original query
        size_t pos = processedInput.find("@" + filePath);
        if (pos != std::string::npos) {
            processedInput.erase(pos, ("@" + filePath).length());
        }
    }

    // Append file contents to the processed input
    if (!fileContents.empty()) {
        processedInput += fileContents;
    }

    string result = parser.parse(processedInput);

    if (result == "UNKNOWN") {
        manager.addEntry("User: " + processedInput);
        std::string fullResponse;
        auto memoryCallback = [&](const std::string& token) {
            fullResponse += token;
            onToken(token);
        };
        interaction.generateResponse(processedInput, memoryCallback);
        manager.addEntry(fullResponse);
        return;
    }

    if (result == "history") {
        manager.showHistory();
    } else if (result == "context") {
        manager.showContext();
    } else if (result == "clear-memory") {
        manager.clearMemory();
    } else if (result == "models") {
        modelManager.listModels();
    } else if (result == "switch") {
        std::vector<std::string> models = modelManager.getModelList();
        std::string selectedModel = UIUtils::selectFromList(models);
        if (!selectedModel.empty()) {
            modelManager.switchModel(selectedModel);
            try {
                interaction.loadModel(modelManager.getCurrentModel());
                onToken("Switched to model: " + selectedModel + "\n");
            } catch (const std::runtime_error& e) {
                onToken("Error switching model: " + std::string(e.what()) + "\n");
            }
        }
    } else if (result.rfind("switch ", 0) == 0) {
        string modelName = result.substr(7);
        modelManager.switchModel(modelName);
        try {
            interaction.loadModel(modelManager.getCurrentModel());
            onToken("Switched to model: " + modelName + "\n");
        } catch (const std::runtime_error& e) {
            onToken("Error switching model: " + std::string(e.what()) + "\n");
        }
    } else {
        onToken(result);
    }
}
