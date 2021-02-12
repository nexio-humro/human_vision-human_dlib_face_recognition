#ifndef FACE_DESCRIPTION_VECTOR_FUNCTIONS_HPP
#define FACE_DESCRIPTION_VECTOR_FUNCTIONS_HPP

#include <iostream>

#include "ros/ros.h"
#include <dlib/image_transforms.h>
#include <human_vision_exchange/FaceDescriptionVector.h>

namespace FDVF
{
	void prepareFaceDescriptionVector(std::vector<dlib::matrix<float,0,1>>& objectVector, human_vision_exchange::FaceDescriptionVector& fdv);
}

#endif
