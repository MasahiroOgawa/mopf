project(image_process)
find_package(OpenCV REQUIRED)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} image visualization opencv_core opencv_features2d)
