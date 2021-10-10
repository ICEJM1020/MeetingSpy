#include "ReadCapture.h"


ReadCapture::ReadCapture()
{
	MainCapture = cv::VideoCapture();
	qDebug() << MainCapture.set(cv::CAP_PROP_FPS, 30);
	qDebug() << MainCapture.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	qDebug() << MainCapture.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

}

ReadCapture::~ReadCapture()
{
	MainCapture.release();
}

cv::Mat ReadCapture::readNowFrame()
{
	MainCapture.read(nowMat);
	return nowMat;
}

void ReadCapture::startCap()
{
	MainCapture.open(0);
}

void ReadCapture::stopCap() {
	MainCapture.release();
}
