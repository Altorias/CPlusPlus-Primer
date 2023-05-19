cmake_minimum_required(VERSION 3.22)
project(LRUClient)

set(CMAKE_CXX_STANDARD 11)

add_executable(LRUClient main.cpp Client.cpp Client.h)

target_link_libraries(LRUClient -ljsoncpp)