project(optimization)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")

file(GLOB SRC_LIST *.cpp *.tpp)
add_library(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} linear_algebra visualization)

add_subdirectory(test)
