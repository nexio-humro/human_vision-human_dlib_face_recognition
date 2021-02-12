#include <ZedData.hpp>

namespace
{
	std::mutex zedDataMutex;
	
	cv::Mat imageData;
	sl::Objects objectsData;
	std::vector<sl::ObjectData> objectsVector;
}

namespace ZD
{
	void saveImage(cv_bridge::CvImagePtr image)
	{
		zedDataMutex.lock();
		imageData = image->image.clone();
		zedDataMutex.unlock();
	}
	
	cv::Mat getImage()
	{
		cv::Mat result;
		
		zedDataMutex.lock();
		result = imageData.clone();
		zedDataMutex.unlock();
		
		return result;
	}
	
	void saveObjects(sl::Objects& objects)
	{
		zedDataMutex.lock();
		objectsData = objects;
		zedDataMutex.unlock();
	}
	
	sl::Objects getObjects()
	{
		sl::Objects result;
		
		zedDataMutex.lock();
		result = objectsData;
		zedDataMutex.unlock();
		
		return result;
	}
	
	void saveObjectsData(std::vector<sl::ObjectData>& objects)
	{
		zedDataMutex.lock();
		objectsVector = objects;
		zedDataMutex.unlock();
	}
	
	std::vector<sl::ObjectData> getObjectsData()
	{
		std::vector<sl::ObjectData> result;
		
		zedDataMutex.lock();
		result = objectsVector;
		zedDataMutex.unlock();
		
		return result;
	}
}
