cmake_minimum_required(VERSION 3.15)
project(freq)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(freq)

add_executable(freq
        freq/freq.cpp
        freq/freq.h
        freq/main.cpp)
