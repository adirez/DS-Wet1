cmake_minimum_required(VERSION 3.8)
project(Wet1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES SplayTree.h Exceptions.h SplayTreeTest.cpp)
add_executable(Wet1 ${SOURCE_FILES})