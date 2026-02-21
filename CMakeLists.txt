cmake_minimum_required(VERSION 3.5)

project(FileWatcher)
set(CMAKE_CXX_STANDARD 17) 

include_directories(${CMAKE_SOURCE_DIR}/src/)
link_directories(${CMAKE_SOURCE_DIR}/src/)

add_executable(FireWatcher src/main.cpp src/core/FileScanner.h src/core/FileScanner.cpp)

