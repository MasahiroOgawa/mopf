project(video_sample)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(sample_videostabilizer sample_videostabilizer.cpp)
target_link_libraries(sample_videostabilizer video)

add_executable(sample_realsense sample_realsense.cpp)
target_link_libraries(sample_realsense video visualization)
