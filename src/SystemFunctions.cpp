#include <SystemFunctions.hpp>

namespace
{
	std::string pathToCurrentDirectory;
}

namespace SF
{
	std::string getPathToCurrentDirectory()
	{
		if(pathToCurrentDirectory == "")
		{
			pathToCurrentDirectory = ros::package::getPath("human_dlib_face_recognition") + "/src/";
		}
		
		return pathToCurrentDirectory;
	}
}
