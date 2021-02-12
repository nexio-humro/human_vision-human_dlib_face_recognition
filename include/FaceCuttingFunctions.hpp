#ifndef FACE_CUTTING_FUNCTIONS_HPP
#define FACE_CUTTING_FUNCTIONS_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include <sl/Camera.hpp>
#include <dlib/image_transforms.h>
#include <dlib/opencv/cv_image.h>

#include <SlCvConverter.hpp>

namespace FCF
{
	typedef std::pair< std::vector< dlib::matrix<dlib::rgb_pixel> >, std::vector<size_t> > pairFacesImages;
	
	const size_t bodyElementsAmount = 18;
	
	static std::vector<sl::BODY_PARTS> framePartsMinMax = {
								sl::BODY_PARTS::LEFT_EAR,
								sl::BODY_PARTS::RIGHT_EAR,
								sl::BODY_PARTS::LEFT_EYE,
								sl::BODY_PARTS::RIGHT_EYE,
								sl::BODY_PARTS::NOSE,
								sl::BODY_PARTS::NECK };
	
	static std::vector<sl::BODY_PARTS> framePartsNoseDistance = {
								sl::BODY_PARTS::LEFT_EAR,
								sl::BODY_PARTS::RIGHT_EAR,
								sl::BODY_PARTS::NOSE };
								
	cv::Rect getFrameMinMax(std::vector<sl::float2>& points);
	cv::Rect getFrameEarNoseDistance(std::vector<sl::float2>& points);
	
	bool areNosePointsCorrect(std::vector<sl::float2>& points);
	bool isFrameCorrect(const cv::Rect& frame, const cv::Mat& image);
	cv::Mat extractFace(const cv::Mat& image, const cv::Rect frame);
	bool prepareCvFace(cv::Mat& faceImage, int imageSize);
	
	FCF::pairFacesImages extractAllFaces(cv::Mat image, sl::Objects objects, int imageSize = 150);
}

#endif
