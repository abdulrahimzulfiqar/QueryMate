# QueryMate

QueryMate is a powerful, local command-line AI assistant built from scratch using C++ and the `llama.cpp` library. It brings the power of Large Language Models (LLMs) directly to your terminal, completely offline and portable.

## Features

*   **100% Local & Private:** No data leaves your device.
*   **Context Aware:** Maintains conversation history (short-term memory) for natural interactions.
*   **File Integration:** Use `@/path/to/file` syntax to let the AI read and analyze local files.
*   **Multi-Model Support:** Switch between different GGUF models (Llama 3, Gemma, Qwen, etc.) on the fly.
*   **Portable:** Can be compiled and run from a USB drive on compatible machines.

## Architecture

This project uses a modular Object-Oriented design:

*   **`AssistantCore`**: The central controller managing the application flow.
*   **`LlamaInteraction`**: Handles low-level inference using `llama.cpp`.
*   **`MemoryManager`**: Manages conversation history and context window.
*   **`CommandParser`**: Interprets user commands (e.g., `/quit`, `/history`, file references).
*   **`UIUtils`**: Manages the CLI interface.

## Building the Project

Requirements:
*   CMake
*   C++ Compiler (Clang/GCC)
*   Make

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

1.  Download a GGUF model and place it in the `models/` directory.
2.  Run the executable:
    ```bash
    ./build/chat
    ```
3.  Chat naturally or use commands like `/help`.

## Credits

Powered by [llama.cpp](https://github.com/ggerganov/llama.cpp).
