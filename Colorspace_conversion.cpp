#include <stdio.h>
#include <opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <iterator> 
#include <algorithm>
#include <string>

using namespace cv;
using namespace std;

Mat YIQ_to_RGB(Mat src);
Mat RGB_to_YIQ(Mat src);

int main() {
	Mat srcimg;

	cout << "Put your image file in the same folder as hello.cpp" << endl;

	int image_type;
	int accept_input[3] = { 1,2,3 };

	cout << "please enter the color space type of your image. " << endl << "1  RGB" << endl;
	cout << "2  YIQ" << endl;
	cout << "3  YCbCr" << endl;
		
	bool exist = false;
	bool gate;
	while (1) {
		cin >> image_type;
		if (cin.fail()||image_type>3||image_type<0) {
			cin.clear();
			cin.sync();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			exist = find(begin(accept_input), end(accept_input), image_type);
			cout << "Wrong Input!!!" << endl << "------------" << endl;
			cout << "please enter the color space type of your image. " << endl << "1  RGB" << endl;
			cout << "2  YIQ" << endl;
			cout << "3  YCbCr" << endl;
			cin >> image_type;
			continue;
		}
		break;
		
	}

	Mat hsv;

	switch (image_type) {
	case 1:
		//RGB
		srcimg = imread("lenna.jpg");
		imshow("input", srcimg);
		waitKey(0);

		//RGB to YCbCr
		cvtColor(srcimg, hsv, COLOR_BGR2YCrCb);
		imshow("YCbCr", hsv);
		
		//RGB to YIQ
		hsv = RGB_to_YIQ(srcimg);
		imshow("YIQ", hsv);
		waitKey(0);
		break;

	case 2:

		//YIQ
		srcimg = imread("lenna_yiq.jpg");
		imshow("input", srcimg);
		waitKey(0);

		//YIQ to RGB
		hsv = YIQ_to_RGB(srcimg);
		imshow("RGB", hsv);

		//RGB to YCbCr
		cvtColor(hsv, hsv, COLOR_BGR2YCrCb);
		imshow("YCbCr", hsv);
		waitKey(0);
		break;


	case 3:
		//YCbCr
		srcimg = imread("lenna_ycbcr.jpg");
		imshow("input", srcimg);
		waitKey(0);

		//YCbCr to RGB
		cvtColor(srcimg, hsv, COLOR_YCrCb2BGR);
		imshow("RGB", hsv);

		//RGB to YIQ
		hsv = RGB_to_YIQ(hsv);
		imshow("YIQ", hsv);
		waitKey(0);
		break;
	}
	
	if (srcimg.empty()) {
		cout << "No Image Input: " << srcimg << endl;
		return 1;
	}

	return 0;
}

Mat RGB_to_YIQ(Mat src) {
	src.convertTo(src, CV_32FC3);//轉32fc3精度比較高
	Mat YIQ = src.clone();
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++) {
			YIQ.at<Vec3f>(i, j)[2] = (((	0.299*src.at<Vec3f>(i, j)[2] +
											0.587*src.at<Vec3f>(i, j)[1] +
											0.114*src.at<Vec3f>(i, j)[0])) / 255);
			YIQ.at<Vec3f>(i, j)[1] = (((	0.596*src.at<Vec3f>(i, j)[2] +
										   -0.274*src.at<Vec3f>(i, j)[1] +
										   -0.322*src.at<Vec3f>(i, j)[0])) / 255);
			YIQ.at<Vec3f>(i, j)[0] = (((	0.211*src.at<Vec3f>(i, j)[2] +
										   -0.523*src.at<Vec3f>(i, j)[1] +
											0.312*src.at<Vec3f>(i, j)[0])) / 255);
		}
	}
	return YIQ;
}

Mat YIQ_to_RGB(Mat src) {
	
	src.convertTo(src, CV_32FC3);
	Mat RGB = src.clone();

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++) {
			RGB.at<Vec3f>(i, j)[2] = (((	1.0  *src.at<Vec3f>(i, j)[2] +
											0.956*src.at<Vec3f>(i, j)[1] +
											0.619*src.at<Vec3f>(i, j)[0])) / 255);
			RGB.at<Vec3f>(i, j)[1] = (((	1.0  *src.at<Vec3f>(i, j)[2] +
										   -0.272*src.at<Vec3f>(i, j)[1] +
										   -0.647*src.at<Vec3f>(i, j)[0])) / 255);
			RGB.at<Vec3f>(i, j)[0] = (((	1.0  *src.at<Vec3f>(i, j)[2] +
										   -1.106*src.at<Vec3f>(i, j)[1] +
											1.703*src.at<Vec3f>(i, j)[0])) / 255);
		}
	}

	return RGB;
}
