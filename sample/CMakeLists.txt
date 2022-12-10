project(sample)
find_package(OpenCV REQUIRED)

add_executable(video_stabilization src/video_stabilization.cpp)
target_link_libraries(video_stabilization video ${OpenCV_LIBS})
