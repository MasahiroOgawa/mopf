cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

project(mopf)

add_subdirectory(mopf/3d_reconstruction)
add_subdirectory(mopf/algebra)
add_subdirectory(mopf/analysis)
add_subdirectory(mopf/device)
add_subdirectory(ext)
add_subdirectory(mopf/game)
add_subdirectory(mopf/image)
add_subdirectory(mopf/image_process)
add_subdirectory(mopf/linear_algebra)
add_subdirectory(mopf/machine_learning)
add_subdirectory(mopf/optimization)
add_subdirectory(mopf/string_util)
add_subdirectory(mopf/video)
add_subdirectory(mopf/visualization)

add_subdirectory(sample)
