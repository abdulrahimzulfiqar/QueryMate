// 

#pragma once
#include <iostream>
#include <string>
#include "../core/AssistantCore.h"
#include "UIUtils.h"
using namespace std;

// CLI controls user interaction
class CLI {
private:
    AssistantCore core;
    bool running = true;
public:
    void start();
    void handleCommand(const string &input);
};
