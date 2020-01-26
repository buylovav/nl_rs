cmake_minimum_required(VERSION 3.0.2)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED true)

project(rewriter)

add_executable(rewriter main.cpp rewriter.cpp)
target_link_libraries(rewriter pthread)