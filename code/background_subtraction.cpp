#include "opencv2/opencv.hpp"
#include <iostream>

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

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	namedWindow("LiveVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	Mat bframe, bframe_gray;

	bool bSuccess = cap.read(bframe); // read a new frame from video

	imshow("MyVideo", bframe); //show the frame in "MyVideo" window

	vector<int> compression_params; //vector that stores the compression parameters of the image

	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //specify the compression technique

	compression_params.push_back(98); //specify the compression quality

	bSuccess = imwrite("E:/Education/Acads/4-1/LOP/LOP/LOP/BackGrnd.jpg", bframe, compression_params); //write the image to file
	cvtColor(bframe, bframe_gray, CV_RGB2GRAY);
	while (1)
	{
		static Mat frame, foreframe, frame_gray;

		bSuccess = cap.read(frame);
		cvtColor(frame, frame_gray, CV_RGB2GRAY);

		foreframe = abs(frame_gray - bframe_gray);
		//subtract(bframe, frame, foreframe);
		threshold(foreframe, foreframe, 30, 255, THRESH_BINARY);
		
		namedWindow("ForeFrame", CV_WINDOW_AUTOSIZE);
		imshow("LiveVideo", frame);
		imshow("ForeFrame", foreframe);
		if(waitKey(30)>=0) break;
	}

	return 0;

}


