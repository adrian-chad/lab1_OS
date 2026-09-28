cmake_minimum_required(VERSION 3.20)
project(LabWork CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Creator creator.cpp)
add_executable(Reporter reporter.cpp)
add_executable(Main main.cpp)