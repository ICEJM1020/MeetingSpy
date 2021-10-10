#pragma once
#include <opencv2/opencv.hpp>
#include <qdebug.h>

class ReadCapture
{
public:
	ReadCapture();
	~ReadCapture();
	cv::VideoCapture MainCapture;
    cv::Mat nowMat;
	cv::Mat readNowFrame();
	void startCap();
	void stopCap();
};
