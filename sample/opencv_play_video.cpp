#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
int main() 
{
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
	int frame_count = 0;

	while (1) 
	{
		frame_count++;
		frames = pipe.wait_for_frames();
		color = frames.get_color_frame();
		
		if (frame_count == 5)
		{
			frame_count = 0;
			continue;
		}
		
		Mat image(Size(640, 480), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
		imshow("Display image", image);
		if ((char)waitKey(1) == 27)
			break;
		
	}

	pipe.stop();
	destroyAllWindows();

    return 0;

}