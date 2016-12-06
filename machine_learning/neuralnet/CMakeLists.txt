cmake_minimum_required(VERSION 2.8)
project(neuralnet)
set(CMAKE_CXX_FLAGS "-pthread -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")


find_package(OpenCV 3 REQUIRED)
file(GLOB SRCS src/*.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} data_handler)


file(GLOB SRCS src_createdata/*.cpp)
add_executable(create_data ${SRCS})
