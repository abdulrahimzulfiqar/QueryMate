#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <regex> // Added for regex functionality
using namespace std;

// CommandParser maps commands ("/help", "/quit") to functions
class CommandParser {
private:
    unordered_map<string, function<string()>> commands;

public:
    CommandParser();
    string parse(const string &input);
    vector<pair<string, string>> getCommands();
    vector<string> extractFileReferences(const string& input);
};
