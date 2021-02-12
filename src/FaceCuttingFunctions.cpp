#include <FaceCuttingFunctions.hpp>

namespace FCF
{
	cv::Rect getFrameMinMax(std::vector<sl::float2>& points)
	{
		cv::Rect result;
		
		if(areNosePointsCorrect(points))
		{
			cv::Point leftTop(9999.0,9999.0);
			cv::Point rightBottom(-1.0,-1.0);
			
			for(size_t i = 0; i < framePartsMinMax.size(); i++)
			{
				sl::float2 value = points[getIdx(framePartsMinMax.at(i))];
				
				if(value[0] > rightBottom.x)
				{
					rightBottom.x = value[0];
				}
				
				if(value[0] < leftTop.x)
				{
					leftTop.x = value[0];
				}
				
				if(value[1] > rightBottom.y)
				{
					rightBottom.y = value[1];
				}
				
				if(value[1] < leftTop.y)
				{
					leftTop.y = value[1];
				}
			}

			result = cv::Rect(leftTop, rightBottom);
		}
		
		return result;
	}
	
	cv::Rect getFrameEarNoseDistance(std::vector<sl::float2>& points)
	{
		cv::Rect result;
		
		if(FCF::areNosePointsCorrect(points))
		{
			sl::float2 nose_cord = points[getIdx(sl::BODY_PARTS::NOSE)];
			sl::float2 left_ear_cord = points[getIdx(sl::BODY_PARTS::LEFT_EAR)];
			sl::float2 right_ear_cord = points[getIdx(sl::BODY_PARTS::RIGHT_EAR)];
			
			float first_distance = nose_cord.distance(nose_cord, left_ear_cord);
			float second_distance = nose_cord.distance(nose_cord, right_ear_cord);
			
			float longestDistance;
			
			if(first_distance < second_distance)
			{
				longestDistance = second_distance;
			}
			else
			{
				longestDistance = first_distance;
			}
			
			cv::Point leftTop(nose_cord[0] - static_cast<int>(longestDistance), nose_cord[1] - static_cast<int>(longestDistance));
			cv::Point rightBottom(nose_cord[0] + static_cast<int>(longestDistance), nose_cord[1] + static_cast<int>(longestDistance));
			
			result = cv::Rect(leftTop, rightBottom);
		}
		
		return result;
	}
	
	bool areNosePointsCorrect(std::vector<sl::float2>& points)
	{
		bool result = true;
		
		if(points.size() == bodyElementsAmount)
		{
			for(size_t i = 0; i < framePartsNoseDistance.size(); i++)
			{
				sl::float2 value = points[getIdx(framePartsNoseDistance.at(i))];
				
				if(value[0] == -1)
				{
					result = false;
					break;
				}
				
				if(value[1] == -1)
				{
					result = false;
					break;
				}
			}
		}
		else
		{
			result = false;
		}
		
		return result;
	}
	
	bool isFrameCorrect(const cv::Rect& frame, const cv::Mat& image)
	{
		bool result = true;
		
		if( (frame.x < 0) || (frame.y < 0) || ((frame.x + frame.width) >= image.cols) || ((frame.y + frame.height) >= image.rows) || (frame.width == 0) || (frame.height == 0) )
		{
			result = false;
		}
		
		return result;
	}
	
	cv::Mat extractFace(const cv::Mat& image, const  cv::Rect frame)
	{
		cv::Mat result;
		
		if( (FCF::isFrameCorrect(frame, image) == true) && (image.empty() == false) )
		{
			cv::Mat copiedImage = image.clone();
			result = copiedImage(frame);
		}
		
		return result;
	}
	
	bool prepareCvFace(cv::Mat& faceImage, int imageSize)
	{
		bool result = true;
		
		if( (faceImage.empty() == false) && (imageSize > 0) )
		{
			cv::resize(faceImage, faceImage, cv::Size(imageSize, imageSize));
			cv::cvtColor(faceImage, faceImage, cv::COLOR_BGRA2RGB);
		}
		else
		{
			result = false;
		}
		
		return result;
	}
	
	FCF::pairFacesImages extractAllFaces(cv::Mat cv_image, sl::Objects objects, int imageSize)
	{
		std::vector< dlib::matrix<dlib::rgb_pixel> > dlib_faces;
		std::vector< size_t > dlib_faces_indexes;
		
		for (size_t i = 0; i < objects.object_list.size(); i++) 
		{
			bool arePointsOk = FCF::areNosePointsCorrect(objects.object_list.at(i).keypoint_2d);
			
			if(arePointsOk == true)
			{
				cv::Rect frame = FCF::getFrameEarNoseDistance(objects.object_list.at(i).keypoint_2d);
				
				bool isFrameOK = FCF::isFrameCorrect(frame, cv_image);
				
				if(isFrameOK == true)
				{
					cv::Mat faceImage = FCF::extractFace(cv_image, frame);
					bool preparedFace = FCF::prepareCvFace(faceImage, imageSize);
					
					if(preparedFace == true)
					{
						dlib::matrix<dlib::rgb_pixel> matrix_image;
						dlib::assign_image(matrix_image, dlib::cv_image<dlib::rgb_pixel>(faceImage.clone()));
						dlib_faces.push_back(matrix_image);
						dlib_faces_indexes.push_back(i);
					}
				}
			}
		}
		
		FCF::pairFacesImages result(dlib_faces, dlib_faces_indexes);
		
		return result;
	}
}
