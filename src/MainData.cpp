#include <MainData.hpp>

namespace
{
	ros::Publisher faceDescriptionVectorPublisher;
}

namespace MD
{	
	const ros::Publisher* getFaceDescriptionVectorPublisher()
	{
		return &faceDescriptionVectorPublisher;
	}
	
	void setFaceDescriptionVectorPublisher(ros::NodeHandle& node, std::string topicName)
	{
		faceDescriptionVectorPublisher = node.advertise<human_vision_exchange::FaceDescriptionVector>(topicName.c_str(), 10);
	}
}
