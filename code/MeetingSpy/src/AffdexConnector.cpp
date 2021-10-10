#include "AffdexConnector.h"


AffdexConnector::AffdexConnector()
{
	DATA_FOLDER = L"./models/affdex-data";

	faceListenPtr = make_shared<AFaceListener>();
	listenPtr= make_shared<PlottingImageListener>(csvFileStream, draw_display);    // Instanciate the ImageListener class
	videoListenPtr = make_shared<StatusListener>();
	viz = make_shared<Visualizer>();

	frameDetector = make_shared<FrameDetector>(buffer_length, process_framerate, nFaces, (affdex::FaceDetectorMode) faceDetectorMode);
	if_set = setDetector();
	start_time = std::chrono::system_clock::now();
}

cv::Mat AffdexConnector::processOn(cv::Mat input) {
	nowFrame = input;
	if (if_set) {
		return processFrame();
	}
	else {
		return input;
	}
	return nowFrame;
}

bool AffdexConnector::processOff()
{
	frameDetector->stop();
	return true;
}

bool AffdexConnector::setDetector()
{
	frameDetector->setClassifierPath(DATA_FOLDER);
	frameDetector->setDetectAllEmotions(true);
	frameDetector->setDetectAllExpressions(true);
	frameDetector->setDetectAllEmojis(true);
	frameDetector->setDetectAllAppearances(true);
	frameDetector->setImageListener(listenPtr.get());
	frameDetector->setFaceListener(faceListenPtr.get());
	frameDetector->setProcessStatusListener(videoListenPtr.get());
	return true;
}

cv::Mat AffdexConnector::processFrame()
{
	frameDetector->start();
	const auto milliseconds = std::chrono::duration<double>(std::chrono::system_clock::now()-start_time);
	const double seconds = milliseconds.count();

	Frame f(nowFrame.size().width, nowFrame.size().height, nowFrame.data, Frame::COLOR_FORMAT::BGR, seconds);
	frameDetector->process(f);
	if (listenPtr->getDataSize() > 0) {
		std::pair<Frame, std::map<FaceId, Face> > dataPoint = listenPtr->getData();

		Frame frame = dataPoint.first;
		std::map<FaceId, Face> faces = dataPoint.second;

		viz->updateImage(nowFrame);

		std::shared_ptr<unsigned char> imgdata = frame.getBGRByteArray();
		
		for (auto & face_id_pair : faces)
		{
			Face f = face_id_pair.second;
			VecFeaturePoint points = f.featurePoints;
			std::vector<cv::Point2f> bounding_box = CalculateBoundingBox(points);

			viz->drawBoundingBox(bounding_box[0], bounding_box[1], f.faceQuality.brightness);

			doneFrame = viz->showImage();
		}
		viz->writeFaceData(faces);

		return doneFrame;
	}

	return nowFrame;
}

std::vector<cv::Point2f> AffdexConnector::CalculateBoundingBox(VecFeaturePoint points)
{
	std::vector<cv::Point2f> ret;
	//Top Left
	ret.push_back(minPoint(points));
	//Bottom Right
	ret.push_back(maxPoint(points));
	//Top Right
	ret.push_back(cv::Point2f(ret[1].x,ret[0].y));
	//Bottom Left
	ret.push_back(cv::Point2f(ret[0].x,ret[1].y));
	return ret;
}

cv::Point2f AffdexConnector::minPoint(VecFeaturePoint points)
{
	VecFeaturePoint::iterator it = points.begin();
	FeaturePoint ret = *it;
	for (; it != points.end(); it++)
	{
		if (it->x < ret.x) ret.x = it->x;
		if (it->y < ret.y) ret.y = it->y;
	}
	return cv::Point2f(ret.x, ret.y);
}

cv::Point2f AffdexConnector::maxPoint(VecFeaturePoint points)
{
	VecFeaturePoint::iterator it = points.begin();
	FeaturePoint ret = *it;
	for (; it != points.end(); it++)
	{
		if (it->x > ret.x) ret.x = it->x;
		if (it->y > ret.y) ret.y = it->y;
	}
	return cv::Point2f(ret.x, ret.y);
}

