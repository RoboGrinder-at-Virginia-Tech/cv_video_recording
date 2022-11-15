#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;

int main() {	
	VideoCapture cap(0);

	int frame_width = cap.get(CAP_PROP_FRAME_WIDTH); 
	int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

	// Generate VideoWriter using filename, codec, fps, and framesize
	VideoWriter videoWriter("test.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), 30.0, Size(frame_width, frame_height), true);
	

	while (true) 
	{
		Mat frame;
		
		cap >> frame;
  
	    // If the frame is empty, break immediately
	    if (frame.empty())
	      break;
	       
	    // Display the resulting frame    
	    imshow( "Frame", frame );
	 
		// Write frame to videoWriter
		videoWriter.write(frame);

		if ((char)waitKey(1) == 27)
			break;
	}
	cap.release();
	videoWriter.release();
	destroyAllWindows();

    return 0;
    
}