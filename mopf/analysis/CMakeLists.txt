project(analysis)

aux_source_directory(src SRCS)
add_library(${PROJECT_NAME} ${SRCS})
