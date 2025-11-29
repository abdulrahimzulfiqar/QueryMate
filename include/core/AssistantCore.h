#pragma once
#include <string>
#include "CommandParser.h"
#include "MemoryManager.h"
#include <memory>
#include "ModelManager.h"
#include "LlamaInteraction.h"
#include "../../external/llama.cpp/include/llama.h"


using namespace std;

// Handles main query logic
class AssistantCore {
private:
    CommandParser parser;
    MemoryManager manager;
    ModelManager modelManager;
    LlamaInteraction interaction;


public:
    AssistantCore();
    ~AssistantCore();
    void processQuery(const string &input, std::function<void(const std::string&)> onToken);
    string getModelName() const { return modelManager.getCurrentModel(); }
};