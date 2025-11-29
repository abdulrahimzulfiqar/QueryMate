#include "utils/UIUtils.h"
#include "core/AssistantCore.h"
#include <iostream>
#include <functional>

void initiateChat() {
    UIUtils::showLogo();
    UIUtils::showTips();

    try {
        AssistantCore core;
        CommandParser parser; // Initialize CommandParser once

        while (true) {
            UIUtils::printDivider();
            std::cout << "Enter query:\n";
            std::string query;
            std::getline(std::cin, query);

            if (query.empty()) continue;

            if (query == "/") {
                query = UIUtils::selectCommand(parser.getCommands());
                if (query.empty()) continue; // If user cancels selection
            }

            bool shouldQuit = false;

            // Define the callback function for streaming output
            auto onToken = [&](const std::string& token) {
                if (token == "quit") {
                    shouldQuit = true;
                    return;
                }
                std::cout << token;
                fflush(stdout);
            };

            // Some commands print their own output. This is a workaround for the
            // current design of ModelManager and MemoryManager.
            bool isSelfPrintingCommand = (query == "/history" || query == "/context" || query == "/models" || query == "/clear-memory");

            core.processQuery(query, onToken);

            if (shouldQuit) {
                break;
            }

            // Add a newline at the end, unless it was a command that prints its own output.
            if (!isSelfPrintingCommand) {
                 std::cout << std::endl;
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[]) {
    initiateChat();
    return 0;
}