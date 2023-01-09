project(analysis)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
