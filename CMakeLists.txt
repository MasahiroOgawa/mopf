cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Debug")

project(mopf)
add_subdirectory(linear_algebra/src)
add_subdirectory(optimization/src)
