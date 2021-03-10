#include <dlib/image_io.h>

#include <SystemFunctions.hpp>
#include <DlibFrontalFaceDetection.hpp>
#include <DlibFrontalFaceDetectionPaths.hpp>
#include <RosServices.hpp>

#include "ros/ros.h"
#include "ros/package.h"

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "human_dlib_face_recognition");
	ros::NodeHandle node("/human_dlib_face_recognition/");
	
	std::string path = DFFDP::getPathToDetector();
	DlibFrontalFaceDetection::instance()->loadModel(path.c_str());
	
	ros::ServiceServer faceVectorService = node.advertiseService("findFaceVectors", RS::computeFaceVectors);
	
	ros::spin();
    return 0;
}
