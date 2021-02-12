#ifndef SL_CV_CONVERTER_HPP
#define SL_CV_CONVERTER_HPP

#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include <sl/Camera.hpp>

namespace SCC
{
	cv::Mat slMat2cvMat(sl::Mat& input);
}

#endif
