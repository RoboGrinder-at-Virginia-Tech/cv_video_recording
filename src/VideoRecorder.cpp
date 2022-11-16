#include <iostream>
#include <chrono>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include "VideoRecorder.h"

using namespace cv;
using namespace std::chrono_literals;

VideoRecorder::VideoRecorder()
{
	std::cout << "Loading video recording..." << std::endl;
	this->record();
}

int VideoRecorder::record() try
{
	// Config and start pipeline to stream on 30FPS
	auto pipe = std::make_shared<rs2::pipeline>();
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
	pipe->start(cfg);
	
	// Generate VideoWriter using filename, codec, fps, and framesize
	VideoWriter videoWriter("video.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), 30.0, Size(640, 480), true);

	rs2::frameset frames;
	rs2::frame color;
	Mat image;
	for (int i = 0; i < 30; i++)
    {
    	frames = pipe->wait_for_frames();
    }

 	auto finish = std::chrono::system_clock::now() + 1min;

	while (std::chrono::system_clock::now() <= finish) 
	{
		frames = pipe->wait_for_frames();
		color = frames.get_color_frame();
		
		image = Mat(Size(640, 480), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
		imshow("Display video", image);

		// Write frame to videoWriter
		videoWriter.write(image);

		if ((char)waitKey(1) == 27)
			break;
	}

	pipe->stop();
	destroyAllWindows();

    return 0;
    
}
catch (const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}

