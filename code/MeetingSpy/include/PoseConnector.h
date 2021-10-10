#pragma once

#include "openpose/headers.hpp"
#include <opencv2/opencv.hpp>
#include <qdebug.h>

#include "DataProcess.h"

using namespace dp;

class PoseConnector {

public:
	PoseConnector();
	~PoseConnector();
	cv::Mat process(cv::Mat originPic);
	std::shared_ptr<op::Wrapper> opWrapper;
	dp::JointData newJointData;

	void ConfigWrapper(op::Wrapper& opWrapper);
	bool pushJointData(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr);
	cv::Mat display(cv::Mat drawedPic);
};

