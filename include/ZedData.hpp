#ifndef ZED_DATA_HPP
#define ZED_DATA_HPP

#include <iostream>
#include <mutex>

#include "ros/ros.h"
#include "ros/package.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <sl/Camera.hpp>

namespace ZD
{
//	sl::image
	void saveImage(cv_bridge::CvImagePtr image);
	cv::Mat getImage();
	
	void saveObjects(sl::Objects& objects);
	sl::Objects getObjects();
}

#endif

