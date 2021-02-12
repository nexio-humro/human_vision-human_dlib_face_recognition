#ifndef MAIN_DATA_HPP
#define MAIN_DATA_HPP

#include <iostream>

#include <iostream>

#include "ros/ros.h"
#include "human_vision_exchange/FaceDescriptionVector.h"

namespace MD
{
	const ros::Publisher* getFaceDescriptionVectorPublisher();
	void setFaceDescriptionVectorPublisher(ros::NodeHandle& node, std::string topicName);
}

#endif
