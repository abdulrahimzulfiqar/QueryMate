#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
using namespace std;

class ModelManager {
private:
    string currentModel;
    string modelsPath = "/Users/teamincredibles/Desktop/Downloads/QueryMate/models/";

public:
    ModelManager();
    void listModels();
    void switchModel(const std::string &modelName);
    std::string getCurrentModel() const { return modelsPath + currentModel; }
    std::vector<std::string> getModelList();
};
