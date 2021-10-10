#include "DataProcess.h"


void dp::putData(personData data)
{
	std::lock_guard<std::mutex> lg(DataMutex);

	if (dp::DataStack.size() <= 15) {
		dp::DataStack.push(data);
	}
}

void dp::putFaceData(FaceData data)
{
	tempPersonData.faceData = data;
	//putData(tempPersonData);
}

void dp::putJointData(JointData data)
{
	tempPersonData.jointData = data;

	putData(tempPersonData);
}

dp::personData dp::getData(bool if_del)
{
	std::lock_guard<std::mutex> lg(dp::DataMutex);

	if (!dp::DataStack.empty())
	{
		personData temp = dp::DataStack.front();
		if (if_del) dp::DataStack.pop();
		return temp;
	}
	else {
		return empty;
	}
}

int dp::stackStatus()
{
	return dp::DataStack.size();
}

void dp::putResult(Result re)
{
	std::lock_guard<std::mutex> lg(dp::ResultMutex);
	dp::ResultStack.push(re);
}

int dp::resultStatus()
{
	return dp::ResultStack.size();
}

dp::Result dp::getResult()
{
	std::lock_guard<std::mutex> lg(dp::ResultMutex);
	dp::Result re;
	int count = dp::resultStatus();
	if (count < 1) {
		re.anxious = -1;
	}
	else {
		for (int i = 0; i < count; i++) {
			auto temp = dp::ResultStack.front();
			dp::ResultStack.pop();
			re.anxious += temp.anxious;
			re.distracted += temp.distracted;
			re.relaxed += temp.relaxed;
		}
		re.anxious /= count;
		re.distracted /= count;
		re.relaxed /= count;
	}
	std::lock_guard<std::mutex> lg_t(dp::TempMutex);
	result = re;
	return result;
}

dp::Result dp::getTemp()
{
	std::lock_guard<std::mutex> lg_t(dp::TempMutex);
	return dp::result;
}
