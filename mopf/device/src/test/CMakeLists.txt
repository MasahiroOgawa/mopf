project(device.test)

#aux_source_directory(. SRC_LIST) #cause error
file(GLOB SRCS *.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} device)

