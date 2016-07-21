cmake_minimum_required(VERSION 3.5)
project(fish)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        fish.cpp)

add_executable(fish ${SOURCE_FILES})