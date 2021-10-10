#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/timer/timer.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <thread>
#include <qdebug.h>
#include <WINDOWS.H>

#include "Frame.h"
#include "Face.h"
#include "FrameDetector.h"
#include "AffdexException.h"

#include "AFaceListener.hpp"
#include "PlottingImageListener.hpp"
#include "StatusListener.hpp"

using namespace std;
using namespace affdex;
using namespace std::chrono;

class AffdexConnector {
public:
	//变量
	shared_ptr<FrameDetector> frameDetector;
	shared_ptr<FaceListener> faceListenPtr;
	shared_ptr<PlottingImageListener> listenPtr;
	shared_ptr<StatusListener> videoListenPtr;
	shared_ptr<Visualizer> viz;

	
	//函数
	AffdexConnector(); //构造函数
	bool processOff();
	cv::Mat processOn(cv::Mat input);

private:
	//变量
	affdex::path DATA_FOLDER;
	std::vector<int> resolution;
	int process_framerate = 30;
	int camera_framerate = 30;
	int buffer_length = 2;
	unsigned int nFaces = 2;
	bool draw_display = true;
	int faceDetectorMode = (int)FaceDetectorMode::SMALL_FACES;


	std::ofstream csvFileStream;
	cv::Mat nowFrame;
	cv::Mat doneFrame;
	bool if_set;
	std::chrono::system_clock::time_point start_time;
	//函数
	bool setDetector();
	cv::Mat processFrame();
	std::vector<cv::Point2f> CalculateBoundingBox(VecFeaturePoint points);
	cv::Point2f minPoint(VecFeaturePoint points);
	cv::Point2f maxPoint(VecFeaturePoint points);
};


