#ifndef ROS_SERVICES_HPP
#define ROS_SERVICES_HPP

#include <iostream>

#include "ros/ros.h"
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <dlib/opencv.h>

#include "human_vision_exchange/FindFaceVectors.h"
#include "human_vision_exchange/FaceDescriptionVector.h"

#include <DlibFrontalFaceDetection.hpp>
#include <FaceDescriptionVectorFunctions.hpp>

namespace RS
{
	bool computeFaceVectors(human_vision_exchange::FindFaceVectors::Request  &req, human_vision_exchange::FindFaceVectors::Response &res);
}

#endif
