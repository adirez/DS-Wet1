cmake_minimum_required(VERSION 3.8)
project(Wet1)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES SplayTree.h Exceptions.h Colosseum.cpp Colosseum.h library1.h library1.cpp
        Trainer.cpp Trainer.h GladiatorID.cpp GladiatorID.h GladiatorLevel.cpp GladiatorLevel.h main1.cpp)
add_executable(Wet1 ${SOURCE_FILES})
