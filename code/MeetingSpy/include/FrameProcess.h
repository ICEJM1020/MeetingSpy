#pragma once

#include "AffdexConnector.h"
#include "PoseConnector.h"

class FrameProcess
{

public:
	//functions
	FrameProcess();
	~FrameProcess();
	cv::Mat Process(cv::Mat frame);

	//variables
	AffdexConnector affConector;
	PoseConnector poseConector;


};

 