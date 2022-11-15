cmake_minimum_required(VERSION 3.24)
project(video_recording)
set(CMAKE_CXX_STANDARD 14)

find_package(realsense2 REQUIRED)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp src/VideoRecorder.cpp)
add_executable(video_record ${SOURCE_FILES})
include_directories(include ${realsense_INCLUDE_DIR} ${OpenCV_INCLUDE_DIR})
target_include_directories(video_record PRIVATE ${realsense_INCLUDE_DIR} ${OpenCV_INCLUDE_DIR})
target_link_libraries(video_record ${realsense2_LIBRARY} ${OpenCV_LIBS})



