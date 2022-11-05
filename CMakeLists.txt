cmake_minimum_required(VERSION 3.1.0)
project( video_recording )
find_package( OpenCV REQUIRED )
find_package( realsense2 REQUIRED )

set( main
    src/video_recording.cpp    
)
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( "/usr/local/include" )
add_executable( video_recording ${main}  )
target_link_libraries( video_recording ${OpenCV_LIBS} )
target_link_libraries( video_recording -lrealsense2)

