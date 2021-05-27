project(string_util.test)

file(GLOB SRC_LIST *.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} string_util)

