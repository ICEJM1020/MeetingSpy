#include "FrameProcess.h"

FrameProcess::FrameProcess()
{

}

FrameProcess::~FrameProcess()
{

}

cv::Mat FrameProcess::Process(cv::Mat frame)
{
	cv::Mat ansFrame;

	ansFrame = affConector.processOn(frame);
	ansFrame = poseConector.process(ansFrame);
	//ansFrame = nowFrame;

	return ansFrame;
}


