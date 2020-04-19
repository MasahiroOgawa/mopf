project(algebra)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})

add_subdirectory(src/test)
