project(game)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV REQUIRED)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} visualization image ${OPENCV_LIBS})

add_subdirectory(src/test)
