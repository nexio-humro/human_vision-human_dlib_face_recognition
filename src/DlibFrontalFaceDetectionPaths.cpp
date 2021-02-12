#include <DlibFrontalFaceDetectionPaths.hpp>

namespace
{
	std::string path_to_model = SF::getPathToCurrentDirectory() + "../model/dlib_face_recognition_resnet_model_v1.dat";
}

namespace DFFDP
{
	std::string getPathToDetector()
	{
		return path_to_model;
	}
}
