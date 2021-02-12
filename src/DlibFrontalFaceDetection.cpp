#include <DlibFrontalFaceDetection.hpp>

DlibFrontalFaceDetection* DlibFrontalFaceDetection::instance()
{
	static DlibFrontalFaceDetection* instance = nullptr;
	
	if(instance == nullptr)
	{
		instance = new DlibFrontalFaceDetection();
	}
	
	return instance;
}
	
DlibFrontalFaceDetection::DlibFrontalFaceDetection()
: _modelLoaded(false)
{
	
}

bool DlibFrontalFaceDetection::loadModel(std::string path_to_model)
{
	bool result = true;
	
	try
	{
		dlib::proxy_deserialize pro_des(path_to_model.c_str());
		this->_modelLoaded = true;
	}
	catch(const dlib::error& error_msg)
	{
		result = false;
	}
	
	return result;
}

std::vector<dlib::matrix<float,0,1>> DlibFrontalFaceDetection::computeFaceVectors(std::vector< dlib::matrix<dlib::rgb_pixel> >& faces)
{
	std::vector<dlib::matrix<float,0,1>> result;
	
	if(this->_modelLoaded == true)
	{
		result = this->_net(faces);
	}
	
	return result;
}

bool DlibFrontalFaceDetection::isModelLoaded()
{
	return this->_modelLoaded;
}

