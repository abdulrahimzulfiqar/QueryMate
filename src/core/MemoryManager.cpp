#include "MemoryManager.h"
#include <filesystem>
#include <algorithm>
namespace fs = std::filesystem;

MemoryManager::MemoryManager() {
    // Ensure data directory exists
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }
    loadMemory();
}

void MemoryManager::loadMemory() {
    history.clear();
    ifstream file(memoryFile);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            history.push_back(line);
        }
        file.close();
    }
}

void MemoryManager::saveMemory() {
    ofstream file(memoryFile, ios::trunc);
    if (file.is_open()) {
        for (const auto& entry : history) {
            file << entry << endl;
        }
        file.close();
    }
}

void MemoryManager::addEntry(const string& entry) {
    history.push_back(entry);
    saveMemory();
}

void MemoryManager::showHistory() const {
    cout << "\n=== 🧠 QueryMate Memory History ===\n";
    if (history.empty()) {
        cout << "No history found.\n";
        return;
    }
    for (const auto& line : history) {
        cout << line << endl;
    }
}

void MemoryManager::showContext() const {
    cout << "\n=== 💬 Recent Context ===\n";
    if (history.empty()) {
        cout << "No context available.\n";
        return;
    }
    int start = max(0, (int)history.size() - contextLimit);
    for (int i = start; i < (int)history.size(); ++i) {
        cout << history[i] << endl;
    }
}

void MemoryManager::clearMemory() {
    history.clear();
    saveMemory();
    cout << "🧹 Memory cleared successfully.\n";
}
