#include <iostream>
#include "opencv2/opencv.hpp"


using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame size : " << dWidth << " x " << dHeight << endl;
	 //create a window called "MyVideo"

	Mat bframe_original(480, 640, CV_8UC3, Scalar(0, 0, 255));
	Mat bframe_processed(480, 640, CV_8UC1, Scalar(0));
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);
	namedWindow("ProcessedVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	vector<int> compression_params; //vector that stores the compression parameters of the image
	
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //specify the compression technique
	
	compression_params.push_back(98); //specify the compression quality

	int fps = cap.get(CV_CAP_PROP_FPS);
	printf("%d\n", fps);
	uchar r, g, b;
	while (1)
	{
		 // read a new frame from video
		

		bool bSuccess = cap.read(bframe_original);
		 //show the frame in "MyVideo" window
		for (int i = 0; i < dHeight; i+=2)
		{
			for (int j = 0; j < dWidth; j+=2)
			{
				
				b = bframe_original.at<Vec3b>(i, j)[0];
				g = bframe_original.at<Vec3b>(i, j)[1];
				r = bframe_original.at<Vec3b>(i, j)[2];
				if ((float)(r - g) / (r + g) <= 0.5 && (float)(r - g) / (r + g) >= 0.0 && (float)b / (r + g) <= 0.5)
				{
					bframe_processed.at<uchar>(i, j) = 255;
					continue;
				}
				/*bframe_processed.at<Vec3b>(i, j)[0] = 0;
				bframe_processed.at<Vec3b>(i, j)[1] = 0;
				bframe_processed.at<Vec3b>(i, j)[2] = 0;*/
				bframe_processed.at<uchar>(i, j) = 0;

			}
		}
		imshow("MyVideo", bframe_original);
		imshow("ProcessedVideo", bframe_processed);
		
		waitKey(30);
	}
	
	return 0;
}



