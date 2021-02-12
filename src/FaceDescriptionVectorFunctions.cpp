#include <FaceDescriptionVectorFunctions.hpp>

namespace FDVF
{
	void prepareFaceDescriptionVector(std::vector<dlib::matrix<float,0,1>>& objectVector, human_vision_exchange::FaceDescriptionVector& fdv)
	{
		fdv.faces.resize(objectVector.size());
		for(size_t i = 0; i < objectVector.size(); i++)
		{
			human_vision_exchange::FaceDescription fd;
			for(size_t j = 0; j < objectVector.at(i).size(); j++)
			{
				fd.points[j] = objectVector.at(i)(j);
			}
			fdv.faces[i] = fd;
		}
	}
}
