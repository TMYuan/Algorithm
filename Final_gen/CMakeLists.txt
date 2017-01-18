cmake_minimum_required(VERSION 3.6)
project(Final_gen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Final_gen ${SOURCE_FILES})