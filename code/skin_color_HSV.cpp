#include "opencv2/opencv.hpp"
//#include "cv.h"
//#include "cxcore.h"
//#include "highgui.h"
#include "math.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <sstream>
using namespace std;

using namespace cv;

int main()

{

	int c = 0;

	CvCapture* capture = cvCaptureFromCAM(0);

	if (!cvQueryFrame(capture)){ cout << "Video capture failed, please check the camera." << endl; }
	else{ cout << "Video camera capture status: OK" << endl; };

	CvSize sz = cvGetSize(cvQueryFrame(capture));

	Mat bframe_original(480, 640, CV_8UC3, Scalar(0, 0, 255));
	Mat hsv_image(480, 640, CV_8UC3, Scalar(0, 0, 255));
	Mat bframe_processed(480, 640, CV_8UC1, Scalar(0));
	Mat median(480, 640, CV_8UC1, Scalar(0));

	Rect bounding_rect;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	cvNamedWindow("src", 1);
	namedWindow("ProcessedVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	namedWindow("Contour", CV_WINDOW_AUTOSIZE);
	namedWindow("Hull demo", CV_WINDOW_AUTOSIZE);

	Scalar  hsv_min = Scalar(0, 30, 80);
	Scalar  hsv_max = Scalar(20, 150, 255);

	vector<int> compression_params; //vector that stores the compression parameters of the image
	
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //specify the compression technique
	
	compression_params.push_back(98); //specify the compression quality
	
	int erosion_size = 1;
	int dilation_size = 3;
	Mat element_erosion = getStructuringElement(cv::MORPH_CROSS,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));
	Mat element_dilation = getStructuringElement(cv::MORPH_CROSS,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		cv::Point(dilation_size, dilation_size));


	while (c != 27)

	{
		Mat contour = Mat(480, 640, CV_8UC1, Scalar(0));
		Mat drawing = Mat(480, 640, CV_8UC1, Scalar(0));
		bframe_original = cvQueryFrame(capture);

		//imshow("src", bframe_original);

		cvtColor(bframe_original, hsv_image, CV_BGR2HSV);

		inRange(hsv_image, hsv_min, hsv_max, bframe_processed);
		
		//imshow("hsv-msk", bframe_processed);

		GaussianBlur(bframe_processed, median, Size(7, 7), 0.0, 0.0, BORDER_DEFAULT);

		threshold(median, median, 70, 255, THRESH_BINARY + THRESH_OTSU);
		erode(median, median, element_erosion);
		medianBlur(median, median, 3);
		dilate(median, median, element_dilation);

		findContours(median, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		if (contours.size() > 0)
		{
			vector<vector<Point>> hull(contours.size());
			//vector<vector<Vec4i>> convDef(contours.size());
			//vector<vector<int> >hullIdx(contours.size());
			//vector<vector<Point>> defect_points(contours.size());


			Scalar color = Scalar(255);
			double area = 0.0, max_area = 0.0;
			int i, ci = 0;
			vector <Point> cnt;
			for (i = 0; i < contours.size(); i++)
			{
				convexHull(Mat(contours[i]), hull[i], false);

				drawContours(contour, contours, i, color, 1, 8, hierarchy, 0, Point());
				cnt = contours[i];
				area = contourArea(cnt, false);
				if (area > max_area)
				{
					max_area = area;
					ci = i;
				}
			}
			bounding_rect = boundingRect(contours[ci]);
			Moments mu = moments(contours[ci], false);
			Point centre(mu.m10 / mu.m00, mu.m01 / mu.m00);

			color = Scalar(127);
			drawContours(drawing, contours, ci, color, 1, 8, hierarchy, 0, Point());
			color = Scalar(63);
			drawContours(drawing, hull, ci, color, 1, 8, hierarchy, 0, Point());
			line(drawing, centre, centre, Scalar(255), 2, 8);
			circle(drawing, centre, 130, Scalar(255), 1, 8);

		}
		imshow("src", bframe_original);
		imshow("ProcessedVideo", median);
		imshow("Contour", contour);
		imshow("Hull demo", drawing);

		c = cvWaitKey(10);
	}

	cvReleaseCapture(&capture);

	cvDestroyAllWindows();



}