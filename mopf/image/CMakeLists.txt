project(image)
find_package(OpenCV REQUIRED)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} opencv_core opencv_features2d)

add_subdirectory(src/test)
