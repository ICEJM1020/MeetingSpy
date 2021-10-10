#pragma once

#include <queue>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <qdebug.h>



namespace dp {

	struct FaceData
	{
		double attention = -1.0;
		double browfurrow = -1.0;
		double browraise = -1.0;
		double engagement = -1.0;
		double joy = -1.0;
		double disgust = -1.0;
		double pitch = -1.0;
		double roll = -1.0;
		double yaw = -1.0;
	};

	struct JointData
	{
		cv::Point UpCenter{ -1.0, -1.0};
		cv::Point REar{ -1.0, -1.0};
		cv::Point REye{ -1.0, -1.0};
		cv::Point Nose{ -1.0, -1.0};
		cv::Point LEar{ -1.0, -1.0};
		cv::Point LEye{ -1.0, -1.0};
		cv::Point RS{ -1.0, -1.0};
		cv::Point RA{ -1.0, -1.0};
		cv::Point RH{ -1.0, -1.0};
		cv::Point LS{ -1.0, -1.0};
		cv::Point LA{ -1.0, -1.0};
		cv::Point LH{ -1.0, -1.0};
	};

	struct personData
	{
		FaceData faceData;
		JointData jointData;


		std::string to_str(){
			return std::to_string(faceData.attention) + "," + std::to_string(faceData.disgust) + "," +
				std::to_string(faceData.engagement) + "," + std::to_string(faceData.joy) + "," +
				std::to_string(faceData.browfurrow) + "," + std::to_string(faceData.browraise) + "," +
				std::to_string(faceData.pitch) + "," + std::to_string(faceData.roll) + "," +
				std::to_string(faceData.yaw) + "," +
				std::to_string(jointData.Nose.x) + "," + std::to_string(jointData.Nose.y) + "," +
				std::to_string(jointData.UpCenter.x) + "," + std::to_string(jointData.UpCenter.y) + "," +
				std::to_string(jointData.LEar.x) + "," + std::to_string(jointData.LEar.y) + "," +
				std::to_string(jointData.LEye.x) + "," + std::to_string(jointData.LEye.y) + "," +
				std::to_string(jointData.REye.x) + "," + std::to_string(jointData.REye.y) + "," +
				std::to_string(jointData.REar.x) + "," + std::to_string(jointData.REar.y) + "," +
				std::to_string(jointData.LS.x) + "," + std::to_string(jointData.LS.y) + "," +
				std::to_string(jointData.LA.x) + "," + std::to_string(jointData.LA.y) + "," +
				std::to_string(jointData.LH.x) + "," + std::to_string(jointData.LH.y) + "," +
				std::to_string(jointData.RS.x) + "," + std::to_string(jointData.RS.y) + "," +
				std::to_string(jointData.RA.x) + "," + std::to_string(jointData.RA.y) + "," +
				std::to_string(jointData.RH.x) + "," + std::to_string(jointData.RH.y);
		}
	};

	static struct Result {
		double relaxed = 0;  //0
		double anxious = 0;  //1
		double distracted = 0; //2
	};

	static std::queue<personData> DataStack;
	static std::queue<Result> ResultStack;
	static personData empty;
	static personData tempPersonData;
	static std::mutex DataMutex;
	static std::mutex ResultMutex;
	static std::mutex TempMutex;
	static Result result;

	void putData(personData data);

	void putFaceData(FaceData data);

	void putJointData(JointData data);

	int stackStatus();

	void putResult(Result re);

	int resultStatus();

	Result getResult();

	personData getData(bool if_del);
	
	Result getTemp();
}

