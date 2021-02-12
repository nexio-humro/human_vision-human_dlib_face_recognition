#include <sl/Camera.hpp>
#include <dlib/image_io.h>

#include <SystemFunctions.hpp>
#include <DlibFrontalFaceDetection.hpp>
#include <FaceCuttingFunctions.hpp>
#include <DlibFrontalFaceDetectionPaths.hpp>
#include <RosTopics.hpp>
#include <MainData.hpp>
#include <FaceDescriptionVectorFunctions.hpp>

#include "ros/ros.h"
#include "ros/package.h"

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "human_recognition");
	ros::NodeHandle node("/human_recognition/");
	
	ros::Rate loop_rate(10);

	ros::Subscriber imageGetter = node.subscribe("/zed2/zed_node/left/image_rect_color", 1000, RT::grab_image);
	ros::Subscriber objectsGetter = node.subscribe("/zed2/zed_node/obj_det/objects", 1000, RT::grab_objects);
	
	MD::setFaceDescriptionVectorPublisher(node, "FaceVectors");
	
	std::string path = DFFDP::getPathToDetector();
	DlibFrontalFaceDetection::instance()->loadModel(path.c_str());
		
	FCF::pairFacesImages faces;
	
	while (ros::ok())
	{
		sl::Objects objects = ZD::getObjects();
		cv::Mat photo = ZD::getImage();
		faces = FCF::extractAllFaces(photo, objects);
		
		// save images
		if(true)
		{
			static size_t counter = 0;
			std::string pathImage = SF::getPathToCurrentDirectory() + "../output/image_" + std::to_string(counter) + ".png";
			cv::imwrite (pathImage.c_str(), photo);
			std::cout<<"-----------------------------"<<std::endl;
			std::cout<<"counter "<<counter<<" = "<<std::endl;
			for(size_t i = 0; i < faces.first.size(); i++)
			{
				std::string path = SF::getPathToCurrentDirectory() + "../output/face_" + std::to_string(counter) + "_" + std::to_string(i) + ".png";
				dlib::save_png (faces.first.at(i), path);
			}
			counter++;
		}
		
		std::vector<dlib::matrix<float,0,1>> faceDescriptions;
		faceDescriptions = DlibFrontalFaceDetection::instance()->computeFaceVectors(faces.first);

		// print face vector
		if(false)
		{
			std::cout<<"face vectors:"<<std::endl;
			for(size_t i = 0; i < faceDescriptions.size(); i++)
			{
				std::cout<<"face["<<i<<"]: cols = "<<faceDescriptions.at(i).nc()<<", rows = "<<faceDescriptions.at(i).nr()<<", size = "<<faceDescriptions.at(i).size()<<std::endl;
				for(size_t j = 0; j < faceDescriptions.at(i).size(); j++)
				{
					std::cout<<faceDescriptions.at(i)(j)<<std::endl;
				}
				std::cout<<"---------------------------"<<std::endl;
			}
		}

		// publish faceDescription vector
		if(faceDescriptions.size() > 0)
		{
			human_vision_exchange::FaceDescriptionVector faceVector;
			FDVF::prepareFaceDescriptionVector(faceDescriptions, faceVector);
			MD::getFaceDescriptionVectorPublisher()->publish(faceVector);
		}     

		ros::spinOnce();

		loop_rate.sleep();
	}
    
    return 0;
}
