#include "CommandParser.h"
#include <iostream>
#include <sstream>

using namespace std;

CommandParser::CommandParser() {
    // Register core commands
    commands["/about"] = []() {
        return "QueryMate v1.0 — Offline Modular AI CLI Assistant\nBuilt in C++ using OOP principles.\n";
    };

    commands["/clear"] = []() {
#if defined(_WIN32)
        system("cls");
#else
        system("clear");
#endif
        return "Screen cleared.\n";
    };

    commands["/quit"] = []() {
        return "quit";
    };

    commands["/models"] = []() {
        return "models";
    };

    commands["/history"] = []() {
        return "history";
    };

    commands["/context"] = []() {
        return "context";
    };

    commands["/clear-memory"] = []() {
        return "clear-memory";
    };

    commands["/switch"] = []() {
        return "switch";
    };
}

vector<pair<string, string>> CommandParser::getCommands() {
    vector<pair<string, string>> commandList;
    commandList.push_back({"/models", "List available models"});
    commandList.push_back({"/switch", "Interactively switch models"});
    commandList.push_back({"/clear", "Clear the screen"});
    commandList.push_back({"/history", "Show entire history"});
    commandList.push_back({"/context", "Show short-term context"});
    commandList.push_back({"/clear-memory", "Clear all memory"});
    commandList.push_back({"/about", "Learn about QueryMate"});
    commandList.push_back({"/quit", "Exit QueryMate"});
    return commandList;
}

string CommandParser::parse(const string &input) {
    stringstream ss(input);
    string command;
    ss >> command;

    if (command == "/switch") {
        string modelName;
        if (ss >> modelName) {
            return "switch " + modelName;
        }
    }

    auto it = commands.find(command);
    if (it != commands.end()) {
        return it->second();
    }

    return "UNKNOWN";
}

vector<string> CommandParser::extractFileReferences(const string& input) {
    vector<string> filePaths;
    regex fileRefRegex("@([a-zA-Z0-9_\\./-]+)"); // Regex to match @filename or @path/to/filename
    sregex_iterator it(input.begin(), input.end(), fileRefRegex);
    sregex_iterator end;

    // Get the project root directory (assuming it's the parent of the build directory)
    // This might need to be more robust depending on how the project is structured
    std::string projectRoot = "/Users/teamincredibles/Desktop/Downloads/QueryMate/"; // Hardcoded for now

    for (; it != end; ++it) {
        std::string relativePath = it->str(1); // Group 1 contains the filename/path
        if (relativePath[0] != '/') { // If it's a relative path
            filePaths.push_back(projectRoot + relativePath);
        } else {
            filePaths.push_back(relativePath);
        }
    }
    return filePaths;
}
