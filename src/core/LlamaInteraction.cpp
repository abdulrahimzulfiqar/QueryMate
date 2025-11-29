#include "LlamaInteraction.h"
#include <stdexcept>

LlamaInteraction::LlamaInteraction() {
    llm = std::make_unique<LLMInference>();
}

void LlamaInteraction::loadModel(const std::string &modelPath) {
    llm.reset(new LLMInference());
    // Using default parameters similar to the ones in the old main.cpp
    float temperature = 0.8f;
    float minP = 0.05f;
    long contextSize = 4096;
    int nThreads = 4;
    bool useMmap = true;
    bool useMlock = false;
    bool storeChats = true;

    try {
        // Pass nullptr for chatTemplate to use the model's default
        llm->loadModel(modelPath.c_str(), minP, temperature, storeChats, contextSize, nullptr, nThreads, useMmap, useMlock);
    } catch (const std::runtime_error& e) {
        // Add more context to the error and re-throw
        throw std::runtime_error("LlamaInteraction::loadModel failed: " + std::string(e.what()));
    }
}

void LlamaInteraction::generateResponse(const std::string &prompt, std::function<void(const std::string&)> onToken) {
    llm->startCompletion(prompt.c_str());
    std::string predictedToken;
    while ((predictedToken = llm->completionLoop()) != "[EOG]") {
        onToken(predictedToken);
    }
    llm->stopCompletion(); // Finalize the turn
}

void LlamaInteraction::addChatMessage(const std::string& message, const std::string& role) {
    llm->addChatMessage(message.c_str(), role.c_str());
}