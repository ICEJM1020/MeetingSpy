#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Frame.h>
#include <Face.h>
#include <set>
#include <boost/format.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <qdebug.h>
#include <math.h>
#include <boost/filesystem.hpp>
#include <qobject.h>
#include <time.h>

#include "DataProcess.h"

using namespace affdex;

class Visualizer
{
public:
  Visualizer();
  /** @brief UpdateImage refreshes the image that will be update
  * @param output_img  -- The image to display output on
  */
  void updateImage(cv::Mat output_img);
  void drawBoundingBox(cv::Point2f top_left, cv::Point2f bottom_right, float valence);
  cv::Mat showImage();
  void writeFaceData(std::map<affdex::FaceId, affdex::Face> faces);

private:
  cv::Mat img;
};

class ColorgenRedGreen
{
public:
    /** @brief ColorgenRedGreen
     * @param[in] red_val - Value which will return green
     * @param green_val - Value which will return green
     */
    ColorgenRedGreen( const float red_val, const float green_val )
        :
          red_val_(red_val),
          green_val_(green_val)
    {}

    /** @brief Generate accessor
     * @param val -- Value for which we would like to generate a color
     * @return  BGR Scalar for use in open cv plotting functions (e.g. cv::circle)
     */
    cv::Scalar operator()( const float val ) const;

private:
    const float red_val_;
    const float green_val_;
};

class ColorgenLinear
{
public:
    ColorgenLinear( const float val1, const float val2, cv::Scalar color1, cv::Scalar color2 )
        :
          val1_(val1),
          val2_(val2),
          color1_(color1),
          color2_(color2)
    {}

    /** @brief Generate accessor
     * @param val -- Value for which we would like to generate a color
     * @return  BGR Scalar for use in open cv plotting functions (e.g. cv::circle)
     */
    cv::Scalar operator()( const float val ) const;

private:
  const float val1_;
  const float val2_;

  const cv::Scalar color1_;
  const cv::Scalar color2_;

};
