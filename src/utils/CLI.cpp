#include "CLI.h"
#include <iostream>
#include "termcolor/termcolor.hpp"
#include "core/AssistantCore.h"
#include "UIUtils.h"

using namespace std;

void CLI::start() {
    UIUtils::showLogo();
    UIUtils::showTips();
    UIUtils.printDivider();
    
    cout << "🧠 Active model: " << core.getModelName() << "\n\n";

    string input;
    while (running) {
        cout << termcolor::bright_green << "> " << termcolor::reset;
        getline(cin, input);

        handleCommand(input);
    }
}

void CLI::handleCommand(const string &input) {
    string result = core.processQuery(input);

    if (result == "quit") {
        cout << termcolor::red << "Exiting QueryMate... 👋\n" << termcolor::reset;
        running = false;
        return;
    }

    cout << termcolor::blue << result << "\n";
    UIUtils::printDivider();
}