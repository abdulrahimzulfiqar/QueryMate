#pragma once

#include "LLMInference.h"
#include <string>
#include <memory>

class LlamaInteraction {
private:
    std::unique_ptr<LLMInference> llm;

public:
    LlamaInteraction();

    // Loads a model with sensible default parameters.
    // Throws a std::runtime_error on failure.
    void loadModel(const std::string &modelPath);

    // Generates a response, streaming tokens via the onToken callback.
    void generateResponse(const std::string &prompt, std::function<void(const std::string&)> onToken);

    // Adds a message to the chat history (e.g., a system prompt).
    void addChatMessage(const std::string& message, const std::string& role);
};