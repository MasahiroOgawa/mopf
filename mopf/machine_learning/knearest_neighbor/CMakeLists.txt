project(knearest_neighbor)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} data_handler visualization image)

add_subdirectory(src/test)
