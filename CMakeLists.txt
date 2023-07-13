cmake_minimum_required(VERSION 3.13)  # CMake version check
project(jsoncpp)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard
add_executable(out ./src/main.cpp ./src/json/json.cpp ./src/json/json.h)
