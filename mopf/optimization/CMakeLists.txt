project(optimization)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")

#file(GLOB SRC_LIST *.cpp *.tpp)
aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} linear_algebra visualization)

add_subdirectory(src/test)
