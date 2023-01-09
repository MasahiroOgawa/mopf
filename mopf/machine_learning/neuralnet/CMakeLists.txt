project(neuralnet)
set(CMAKE_CXX_FLAGS "-pthread -std=c++11")
find_package(OpenCV REQUIRED)

file(GLOB SRCS src/*.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} data_handler)

file(GLOB SRCS src_createdata/*.cpp)
add_executable(create_data ${SRCS})
