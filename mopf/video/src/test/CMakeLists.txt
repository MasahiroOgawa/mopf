project(video.test)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")

#aux_source_directory(. SRC_LIST) #cause error
file(GLOB SRC_LIST *.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} video)

