#include <librealsense2/rs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "VideoRecorder.h"

using namespace cv;

VideoRecorder::VideoRecorder()
{
	std::cout << "Loading video recording..." << std::endl;
	this->record();
}

int VideoRecorder::record() try
{
	std::cout << "record!" << std::endl;
	rs2::pipeline pipe;
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
	pipe.start(cfg);

	rs2::frameset frames;
	for (int i = 0; i < 30; i++)
    {
    	frames = pipe.wait_for_frames();
    }

	rs2::frame color;

	while (true) 
	{
		frames = pipe.wait_for_frames();
		color = frames.get_color_frame();
		
		Mat image(Size(640, 480), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
		imshow("Display video", image);
		if ((char)waitKey(1) == 27)
			break;
	}

	pipe.stop();
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

