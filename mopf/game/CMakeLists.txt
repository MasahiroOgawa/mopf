project(game)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} visualization image ${OPENCV_LIBS})

add_subdirectory(src/test)
