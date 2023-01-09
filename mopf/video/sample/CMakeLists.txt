project(video_sample)
find_package(OpenCV REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(sample_videostabilizer sample_videostabilizer)
target_link_libraries(sample_videostabilizer video ${OpenCV_LIBS})
