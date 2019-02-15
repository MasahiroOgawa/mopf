project(game.test)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")

#aux_source_directory(. SRC_LIST) #cause error
add_executable(${PROJECT_NAME} game.test.cpp)
target_link_libraries(${PROJECT_NAME} game)

#add exe of swim_game
add_executable(swim_game swim_game.cpp)
target_link_libraries(swim_game game opencv_highgui)
