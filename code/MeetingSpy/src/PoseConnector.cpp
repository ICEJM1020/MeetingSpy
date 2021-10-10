#include "PoseConnector.h"

PoseConnector::PoseConnector()
{
	//opWrapper = new op::Wrapper(op::ThreadManagerMode::Asynchronous);
	opWrapper = std::make_shared<op::Wrapper>(op::ThreadManagerMode::Asynchronous);
	PoseConnector::ConfigWrapper(*opWrapper);
	
	opWrapper->start();
}

PoseConnector::~PoseConnector()
{
	
}

cv::Mat PoseConnector::process(cv::Mat originPic)
{
	cv::Mat drawPic;
	const auto cvImageToProcess = originPic;
	const op::Matrix imageToProcess = OP_CV2OPCONSTMAT(cvImageToProcess);
	
	auto datumProcessed = opWrapper->emplaceAndPop(imageToProcess);

	if (datumProcessed == nullptr)
	{
		qDebug() << "Image could not be processed";
	}
	else {
		auto data_no_empty = pushJointData(datumProcessed);
		if(data_no_empty) drawPic = display(originPic);
	}
	
	return drawPic;
}

bool PoseConnector::pushJointData(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr)
{
	auto points = datumsPtr->at(0)->poseKeypoints;

	if (!points.empty()) {
		newJointData.Nose = cv::Point(points[0], points[1]);
		newJointData.UpCenter = cv::Point(points[3], points[4]);
		newJointData.REar = cv::Point(points[51], points[52]);
		newJointData.REye = cv::Point(points[45], points[46]);
		newJointData.LEar = cv::Point(points[54], points[55]);
		newJointData.LEye = cv::Point(points[48], points[49]);

		newJointData.RS = cv::Point(points[6], points[7]);
		newJointData.RA = cv::Point(points[9], points[10]);
		newJointData.RH = cv::Point(points[12], points[13]);
		newJointData.LS = cv::Point(points[15], points[16]);
		newJointData.LA = cv::Point(points[18], points[19]);
		newJointData.LH = cv::Point(points[21], points[22]);

		dp::putJointData(newJointData);
		return true;
	}

	dp::JointData empty;
	dp::putJointData(empty);
	return false;
}

void PoseConnector::ConfigWrapper(op::Wrapper & opWrapper)
{ 
	try
	{
		// Configuring OpenPose

		// logging_level
		op::checkBool(0 <= 3 && 3 <= 255, "Wrong logging_level value.",
			__LINE__, __FUNCTION__, __FILE__);
		op::ConfigureLog::setPriorityThreshold((op::Priority)3);
		op::Profiler::setDefaultX(1000);

 		// Pose configuration (use WrapperStructPose{} for default and recommended configuration)
		const op::WrapperStructPose wrapperStructPose{};
		opWrapper.configure(wrapperStructPose);
		// Face configuration (use op::WrapperStructFace{} to disable it)
		const op::WrapperStructFace wrapperStructFace{};
		opWrapper.configure(wrapperStructFace);
		// Hand configuration (use op::WrapperStructHand{} to disable it)
		const op::WrapperStructHand wrapperStructHand{};
		opWrapper.configure(wrapperStructHand);
		// Extra functionality configuration (use op::WrapperStructExtra{} to disable it)
		const op::WrapperStructExtra wrapperStructExtra{};
		opWrapper.configure(wrapperStructExtra);
		// Output (comment or use default argument to disable any output)
		const op::WrapperStructOutput wrapperStructOutput{};
		opWrapper.configure(wrapperStructOutput);
		
	}
	catch (const std::exception& e)
	{
		op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
	}
}

cv::Mat PoseConnector::display(cv::Mat drawedPic)
{
	cv::Mat temp = drawedPic;
	//face
    if (newJointData.REar != cv::Point(0, 0) && newJointData.REye != cv::Point(0, 0)) cv::line(temp, newJointData.REar, newJointData.REye, cv::Scalar(0, 0, 255), 3, 16, 0);
	if (newJointData.REye != cv::Point(0, 0) && newJointData.Nose != cv::Point(0, 0)) cv::line(temp, newJointData.REye, newJointData.Nose, cv::Scalar(0, 0, 255), 3, 16, 0);
	if (newJointData.Nose != cv::Point(0, 0) && newJointData.LEye != cv::Point(0, 0)) cv::line(temp, newJointData.Nose, newJointData.LEye, cv::Scalar(0, 0, 255), 3, 16, 0);
	if (newJointData.LEar != cv::Point(0, 0) && newJointData.LEye != cv::Point(0, 0)) cv::line(temp, newJointData.LEye, newJointData.LEar, cv::Scalar(0, 0, 255), 3, 16, 0);
	//arm
	if (newJointData.LH != cv::Point(0, 0) && newJointData.LA != cv::Point(0, 0)) cv::line(temp, newJointData.LH, newJointData.LA, cv::Scalar(0, 255, 255), 3, 16, 0);
	if (newJointData.LA != cv::Point(0, 0) && newJointData.LS != cv::Point(0, 0)) cv::line(temp, newJointData.LA, newJointData.LS, cv::Scalar(0, 255, 255), 3, 16, 0);
	if (newJointData.RH != cv::Point(0, 0) && newJointData.RA != cv::Point(0, 0)) cv::line(temp, newJointData.RH, newJointData.RA, cv::Scalar(0, 255, 255), 3, 16, 0);
	if (newJointData.RA != cv::Point(0, 0) && newJointData.RS != cv::Point(0, 0)) cv::line(temp, newJointData.RA, newJointData.RS, cv::Scalar(0, 255, 255), 3, 16, 0);
	//body
	if (newJointData.UpCenter != cv::Point(0, 0) && newJointData.Nose != cv::Point(0, 0)) cv::line(temp, newJointData.UpCenter, newJointData.Nose, cv::Scalar(255, 0, 0), 3, 16, 0);
	if (newJointData.UpCenter != cv::Point(0, 0) && newJointData.RS != cv::Point(0, 0)) cv::line(temp, newJointData.UpCenter, newJointData.RS, cv::Scalar(255, 0, 0), 3, 16, 0);
	if (newJointData.UpCenter != cv::Point(0, 0) && newJointData.LS != cv::Point(0, 0)) cv::line(temp, newJointData.UpCenter, newJointData.LS, cv::Scalar(255, 0, 0), 3, 16, 0);

	return temp;
}


