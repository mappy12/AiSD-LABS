cmake_minimum_required(VERSION 3.10)
project(lab2 CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(HashTable "main.cpp" "HashTable.cpp")

add_custom_target(run
    COMMAND make
    COMMAND echo "=== Running program ==="
    COMMAND ./HashTable
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)