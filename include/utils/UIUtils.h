#pragma once
#include <iostream>
#include <termcolor/termcolor.hpp>
#include <vector>
#include <string>

using namespace std;

// Handles colors, logos, and aesthetic parts of UI
class UIUtils {
public:
    static void showLogo();
    static void showTips();
    static void printDivider();
    static std::string selectFromList(const std::vector<std::string>& options);
    static std::string selectCommand(const std::vector<std::pair<std::string, std::string>>& options);
    static std::string readFileContent(const std::string& filePath);
};
