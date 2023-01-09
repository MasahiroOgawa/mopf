project(3d_reconstruction)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} image)

add_subdirectory(src/test)
