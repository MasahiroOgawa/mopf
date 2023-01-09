project(image)
cmake_minimum_required(VERSION 2.8)
find_package(OpenCV REQUIRED)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} opencv_core)

add_subdirectory(src/test)
