cmake_minimum_required(VERSION 2.8.4)
project(HomeWork1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lib/helpers.c lib/helpers.h cat/cat.c)
add_executable(HomeWork1 ${SOURCE_FILES})