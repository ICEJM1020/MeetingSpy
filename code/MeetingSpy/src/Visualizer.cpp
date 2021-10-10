#include "Visualizer.h"

Visualizer::Visualizer()
{
}

void Visualizer::updateImage(cv::Mat output_img)
{
	img = output_img;
}

void Visualizer::drawBoundingBox(cv::Point2f top_left, cv::Point2f bottom_right, float valence)
{ 
    //Draw bounding box
    const ColorgenRedGreen valence_color_generator( -100, 100 );  
	cv::rectangle(img, top_left, bottom_right, valence_color_generator(valence), 2);
}

cv::Mat Visualizer::showImage()
{
	return img;
}

void Visualizer::writeFaceData(std::map<affdex::FaceId, affdex::Face> faces)
{

	double attention = 0;
	double browfurrow = 0;
	double browraise = 0;
	double engagement = 0;
	double joy = 0;
	double disgust = 0;

	double pitch = 0;
	double roll = 0;
	double yaw = 0;
	int numf = 0;

	for (auto & face_id_pair : faces)
	{
		Face f = face_id_pair.second;
		numf++;

		browfurrow = browfurrow + f.expressions.browFurrow;
		browraise = browraise + f.expressions.browRaise;
		attention = attention + f.expressions.attention;
		joy = joy + f.emotions.joy;
		disgust = disgust + f.emotions.disgust;
		engagement = engagement + f.emotions.engagement;

		pitch = pitch + f.measurements.orientation.pitch;
		roll = roll + f.measurements.orientation.roll;
		yaw = yaw + f.measurements.orientation.yaw;
	}

	if (numf != 0) {
		browfurrow = browfurrow / numf;
		browraise = browraise / numf;
		attention = attention / numf;
		joy = joy / numf;
		disgust = disgust / numf;
		engagement = engagement / numf;

		pitch = pitch / numf;
		roll = roll / numf;
		yaw = yaw / numf;
	}
	else {
		attention = -1;
		joy = -1;
		disgust = -1;
		engagement = -1;
	}

	dp::FaceData newData;

	newData.attention = attention;
	newData.joy = joy;
	newData.disgust = disgust;
	newData.engagement = engagement;
	newData.browfurrow = browfurrow;
	newData.browraise = browraise;

	newData.pitch = pitch;
	newData.roll = roll;
	newData.yaw = yaw;

	dp::putFaceData(newData);

	//qDebug() << attention << "," << joy << "," << disgust << "," << engagement;
}

cv::Scalar ColorgenRedGreen::operator()( const float val ) const
{
    float norm_val = ( val - red_val_ ) / ( green_val_ - red_val_ );
    norm_val = norm_val < 0.0 ? 0.0 : norm_val;
    norm_val = norm_val > 1.0 ? 1.0 : norm_val;
    const int B = 0;
    const int G = norm_val * 255;
    const int R = ( 1.0 - norm_val ) * 255;
    return cv::Scalar( B, G, R );
}

cv::Scalar ColorgenLinear::operator()( const float val ) const
{
    float norm_val = ( val - val1_ ) / ( val2_ - val1_ );
    const int B = color1_.val[0] * (1.0f-norm_val) + color2_.val[0]*norm_val;
    const int G = color1_.val[1] * (1.0f-norm_val) + color2_.val[1]*norm_val;
    const int R = color1_.val[2] * (1.0f-norm_val) + color2_.val[2]*norm_val;
    return cv::Scalar( B, G, R );
}
