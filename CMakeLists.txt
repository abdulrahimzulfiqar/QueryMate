# cmake_minimum_required(VERSION 3.10)
# project(QueryMate)

# set(CMAKE_CXX_STANDARD 17)
# set(LLAMA_BUILD_COMMON On)
# add_subdirectory(external/llama.cpp)


# include_directories(include)
# include_directories(include/core)
# include_directories(include/utils)
# include_directories(external/llama.cpp/include)
# include_directories(external/llama.cpp/common)

# add_executable(#QueryMate
#     main.cpp
#     # src/core/AssistantCore.cpp
#     # src/core/CommandParser.cpp
#     src/core/LLMInference.cpp
#     chat
#     # src/core/MemoryManager.cpp
#     # src/core/ModelManager.cpp
#     # src/utils/CLI.cpp
#     # src/utils/UIUtils.cpp
# )


# target_link_libraries(#QueryMate chat PRIVATE common llama ggml)


cmake_minimum_required(VERSION 3.10)
project(llama_inference)

set(CMAKE_CXX_STANDARD 17)
set(LLAMA_BUILD_COMMON On)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1")

add_subdirectory(external/llama.cpp)

include_directories(include)
include_directories(include/core)
include_directories(include/utils)

add_executable(
        chat
        main.cpp
        src/core/AssistantCore.cpp
        src/core/CommandParser.cpp
        src/core/LlamaInteraction.cpp
        src/core/LLMInference.cpp
        src/core/MemoryManager.cpp
        src/core/ModelManager.cpp
        src/utils/UIUtils.cpp
)
target_link_libraries(
        chat
        PRIVATE
        common llama ggml
)