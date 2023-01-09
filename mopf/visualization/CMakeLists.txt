project(visualization)
cmake_minimum_required(VERSION 2.8)
find_package(OpenCV REQUIRED)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} linear_algebra opencv_highgui opencv_imgproc opencv_imgcodecs)

add_subdirectory(src/test)
