project(sample)
include_directories(${mopf_SOURCE_DIR})


add_executable(sample_realsense video/sample_realsense.cpp)
target_link_libraries(sample_realsense video visualization)

add_executable(sample_realsense_stabilizer video/sample_realsense_stabilizer.cpp)
target_link_libraries(sample_realsense_stabilizer video visualization)

add_executable(sample_sift image/sample_sift.cpp)
target_link_libraries(sample_sift image_process image visualization)

add_executable(sample_videostabilizer video/sample_videostabilizer.cpp)
target_link_libraries(sample_videostabilizer video)

add_executable(sample_videostitcher video/sample_videostitcher.cpp)
target_link_libraries(sample_videostitcher image_process video)
