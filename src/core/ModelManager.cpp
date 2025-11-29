#include "ModelManager.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

ModelManager::ModelManager() {
    currentModel = "gemma-3-270m-it-F16.gguf"; // Default model
    cout << "🧠 Default model loaded: " << currentModel << endl;
}

void ModelManager::listModels() {
    if (!fs::exists(modelsPath) || !fs::is_directory(modelsPath)) {
        cout << "❌ Error: Models directory not found at " << modelsPath << endl;
        return;
    }
    cout << "\n📦 Available Models:\n";
    for (const auto &entry : fs::directory_iterator(modelsPath)) {
        if (entry.path().extension() == ".gguf") {
            cout << " - " << entry.path().filename().string() << endl;
        }
    }
}

void ModelManager::switchModel(const string &modelName) {
    string path = modelsPath + modelName;
    if (fs::exists(path)) {
        currentModel = modelName;
        cout << "✅ Switched to model: " << currentModel << endl;
    } else {
        cout << "❌ Model not found: " << modelName << endl;
    }
}

std::vector<std::string> ModelManager::getModelList() {
    std::vector<std::string> models;
    if (!fs::exists(modelsPath) || !fs::is_directory(modelsPath)) {
        return models;
    }
    for (const auto &entry : fs::directory_iterator(modelsPath)) {
        if (entry.path().extension() == ".gguf") {
            models.push_back(entry.path().filename().string());
        }
    }
    return models;
}