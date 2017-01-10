cmake_minimum_required(VERSION 3.6)
project(gamae)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        res/cfx/m4-default.xcf
        res/images/M4/m4-default.png
        arsenal.cpp
        main.cpp
        player.cpp
        player.h
        weapon.h weapon.cpp)

add_executable(gamae ${SOURCE_FILES})