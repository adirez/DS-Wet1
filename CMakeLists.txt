cmake_minimum_required(VERSION 3.8)
project(Wet1)

set(g++ -Wall -DNDEBUG)

set(SOURCE_FILES SplayTree.h Exceptions.h library1.h Colosseum.cpp Colosseum.h library1.cpp SplayTreeTest.cpp)
add_executable(Wet1 ${SOURCE_FILES})