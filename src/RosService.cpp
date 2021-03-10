#include <RosServices.hpp>

namespace RS
{
	bool computeFaceVectors(human_vision_exchange::FindFaceVectors::Request  &req, human_vision_exchange::FindFaceVectors::Response &res)
	{
		std::vector< dlib::matrix<dlib::rgb_pixel> > dlib_faces;
		
		for(size_t i = 0; i < req.faces.size(); i++)
		{
			cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(req.faces[i], sensor_msgs::image_encodings::BGR8);
			cv::Mat faceImage = cv_ptr->image;
			
			dlib::matrix<dlib::rgb_pixel> matrix_image;
			dlib::assign_image(matrix_image, dlib::cv_image<dlib::rgb_pixel>(faceImage.clone()));
			dlib_faces.push_back(matrix_image);
		}

		std::vector<dlib::matrix<float,0,1>> faceDescriptions;		
		faceDescriptions = DlibFrontalFaceDetection::instance()->computeFaceVectors(dlib_faces);
		
		human_vision_exchange::FaceDescriptionVector faceDescriptionVector;
		FDVF::prepareFaceDescriptionVector(faceDescriptions, faceDescriptionVector);

		res.faceVectors = faceDescriptionVector;
		
		return true;
	}
}
