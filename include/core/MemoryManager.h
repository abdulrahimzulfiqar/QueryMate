#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class MemoryManager {
private:
    vector<string> history;          // all user + assistant messages
    const string memoryFile = "data/memory.txt";
    const int contextLimit = 5;      // number of recent lines to keep in context

public:
    MemoryManager();

    // Load saved memory from file
    void loadMemory();

    // Save all memory to file
    void saveMemory();

    // Add a new entry (e.g. user query or assistant response)
    void addEntry(const string& entry);

    // Show entire history
    void showHistory() const;

    // Show short-term context
    void showContext() const;

    // Clear all memory
    void clearMemory();
};
