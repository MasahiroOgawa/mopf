project(video)
find_package(OpenCV REQUIRED)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} image_process visualization image opencv_video opencv_core)

add_subdirectory(src/test)
