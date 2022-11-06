#include <librealsense2/rs.hpp>
#include <iostream>



int main()
{
    // Use to hold a data from camera
    rs2::frameset frames;
    
    int fps = 24;

    // Create a pipeline as a virtual representation of the device
	auto pipe = std::make_shared<rs2::pipeline>();
    rs2::config cfg; // Config the device to record video for a fps of 24 

    // Camera warmup - dropping several first frames to let auto-exposure stabilize
    for(int i = 0; i < 30; i++)
    {
        Wait for all configured streams to produce a frame
        frames = pipe.wait_for_frames();
    }
    // Initialize a shared pointer to a device with the current device on the pipeline
    //rs2::device device = pipe->get_active_profile().get_device();

    cfg.enable_stream(RS2_STREAM_COLOR, RS2_FORMAT_ANY, fps)
    cfg.enable_record_to_file("video.bag");
    pipe->start(cfg); //File will be opened at this point
    
    int total_frame_count = 0;

    while (total_frame_count < fps * 60)
    {
        frames = pipe.wait_for_frames();
        total_frame_count += frames.size();
    }   

    pipe->stop()
    return 0;
}