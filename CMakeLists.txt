cmake_minimum_required(VERSION 3.20)

project(NETRA
    VERSION 0.1.0
    DESCRIPTION "Network Resilience and Self-Healing Routing Engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(netra
    src/main.cpp
    src/graph.cpp
)

target_include_directories(netra
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(netra PRIVATE /W4)
else()
    target_compile_options(netra PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()