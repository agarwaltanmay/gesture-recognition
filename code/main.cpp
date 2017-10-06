#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "bgfg_cb.h"
#include <iostream>
using namespace cv;
using namespace std;
void proc()
{
	Mat frame, fg, gray;
	VideoCapture cap(0);
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
	Mat bframe;
	bool bSuccess = cap.read(bframe);
	initializeCodebook(frame.rows, frame.cols);
	for (;;)
	{
		bool bSuccess = cap.read(bframe);
		cvtColor(frame, gray, CV_BGR2GRAY);
		fg_cb(gray, fg);
		Mat cc;
		imshow("fg", fg);
		waitKey(1);
	}
}

int main(int argc, char ** argv)
{
	proc();
	cin.ignore(1);
	return 0;
}


