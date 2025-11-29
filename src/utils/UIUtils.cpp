#include "UIUtils.h"
#include <termios.h>
#include <unistd.h>
#include <fstream> // Added for file input operations
#include <sstream> // Added for string stream operations
#include <cstring> // Required for strerror
#include <cerrno>  // Required for errno

using namespace std;

void UIUtils::showLogo() {

    cout << termcolor::cyan << "===========================================================================================\n";
cout << R"( 
 $$$$$$\                                          $$\      $$\            $$\               
$$  __$$\                                         $$$\    $$$ |           $$ |              
$$ /  $$ |$$\   $$\  $$$$$$\   $$$$$$\  $$\   $$\ $$$$\  $$$$ | $$$$$$\ $$$$$$\    $$$$$$\  
$$ |  $$ |$$ |  $$ |$$  __$$\ $$  __$$\ $$ |  $$ |$$\$$\$$ $$ | \____$$\\_$$  _|  $$  __$$\ 
$$ |  $$ |$$ |  $$ |$$$$$$$$ |$$ |  \__|$$ |  $$ |$$ \$$$  $$ | $$$$$$$ | $$ |    $$$$$$$$ |
$$ $$\$$ |$$ |  $$ |$$   ____|$$ |      $$ |  $$ |$$ |\$  /$$ |$$  __$$ | $$ |$$\ $$   ____|
\$$$$$$ / \$$$$$$  |\$$$$$$$\ $$ |      \$$$$$$$ |$$ | \_/ $$ |\$$$$$$$ | \$$$$  |\$$$$$$$\ 
 \___$$$\  \______/  \_______|\__|       \____$$ |\__|     \__| \_______|  \____/  \_______|
     \___|                              $$\   $$ |                                          
                                        \$$$$$$  |                                          
                                         \______/                                          
)";
    cout << termcolor::magenta << "===========================================================================================\n";
    cout << termcolor::reset;
}




void UIUtils::showTips() {
    cout << termcolor::bright_white << "Tips for getting started:\n";
    cout << termcolor::yellow << "1." << termcolor::reset << " Ask queries, manage files, or run commands.\n";
    cout << termcolor::yellow << "2." << termcolor::reset << " Stay offline — QueryMate runs locally.\n";
    cout << termcolor::yellow << "3." << termcolor::reset << " Type " << termcolor::cyan << "/ " 
         << termcolor::reset << "to get all available commands.\n\n";
}

void UIUtils::printDivider() {
    cout << termcolor::grey 
         << "----------------------------------------------------\n" 
         << termcolor::reset;
}

std::string UIUtils::selectFromList(const std::vector<std::string>& options) {
    if (options.empty()) {
        return "";
    }

    int selected = 0;
    char c;

    // Switch to raw mode
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (true) {
        // Clear screen and print options
        cout << "\u001b[2J\u001b[1;1H";
        cout << "Select a model:\n";
        for (int i = 0; i < options.size(); ++i) {
            if (i == selected) {
                cout << termcolor::green << ">> " << options[i] << termcolor::reset << "\n";
            } else {
                cout << "   " << options[i] << "\n";
            }
        }

        // Read a character
        char input_buffer[4];
        ssize_t bytes_read = read(STDIN_FILENO, input_buffer, sizeof(input_buffer) - 1);
        if (bytes_read > 0) {
            input_buffer[bytes_read] = '\0';

            if (input_buffer[0] == '\n') { // Enter key
                break;
            } else if (input_buffer[0] == '\x1b') { // Escape sequence
                if (bytes_read >= 3 && input_buffer[1] == '[') {
                    switch(input_buffer[2]) {
                        case 'A': // Up
                            selected = (selected - 1 + options.size()) % options.size();
                            break;
                        case 'B': // Down
                            selected = (selected + 1) % options.size();
                            break;
                    }
                }
            }
        }
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return options[selected];
}

std::string UIUtils::selectCommand(const std::vector<std::pair<std::string, std::string>>& options) {
    if (options.empty()) {
        return "";
    }

    int selected = 0;
    char c;

    // Switch to raw mode
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (true) {
        // Clear screen and print options
        cout << "\u001b[2J\u001b[1;1H";
        cout << "Select a command:\n";
        for (int i = 0; i < options.size(); ++i) {
            if (i == selected) {
                cout << termcolor::green << ">> " << options[i].first << " - " << options[i].second << termcolor::reset << "\n";
            } else {
                cout << "   " << options[i].first << " - " << options[i].second << "\n";
            }
        }

        // Read a character
        char input_buffer[4];
        ssize_t bytes_read = read(STDIN_FILENO, input_buffer, sizeof(input_buffer) - 1);
        if (bytes_read > 0) {
            input_buffer[bytes_read] = '\0';

            if (input_buffer[0] == '\n') { // Enter key
                break;
            } else if (input_buffer[0] == '\x1b') { // Escape sequence
                if (bytes_read >= 3 && input_buffer[1] == '[') {
                    switch(input_buffer[2]) {
                        case 'A': // Up
                            selected = (selected - 1 + options.size()) % options.size();
                            break;
                        case 'B': // Down
                            selected = (selected + 1) % options.size();
                            break;
                    }
                }
            }
        }
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return options[selected].first;
}

std::string UIUtils::readFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "Error: Could not open file " + filePath + ". Reason: " + strerror(errno);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
