#include <RosTopics.hpp>

namespace RT
{
	void grab_image(const sensor_msgs::ImagePtr&  image)
	{
		cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(image, sensor_msgs::image_encodings::BGR8);
		ZD::saveImage(cv_ptr);
	}
	
	void grab_objects(const zed_interfaces::Objects& objects)
	{
		sl::Objects result;
		std::vector<sl::ObjectData> objectsVector;
		
		for(size_t i = 0; i < objects.objects.size(); i++)
		{
			sl::ObjectData obj;
			
			obj.label = sl::OBJECT_CLASS::PERSON;
			obj.id = objects.objects[i].label_id;
			obj.confidence = objects.objects[i].confidence;
			
			obj.position.x = objects.objects[i].position.x;
			obj.position.y = objects.objects[i].position.y;
			obj.position.z = objects.objects[i].position.z;
			
			obj.velocity.x = objects.objects[i].linear_vel.x;
			obj.velocity.y = objects.objects[i].linear_vel.y;
			obj.velocity.z = objects.objects[i].linear_vel.z;
			
			std::vector<sl::uint2> bbox_2d;
            for (size_t c = 0; c < objects.objects[i].bbox_2d.size(); c++) 
            {
				unsigned int x = objects.objects[i].bbox_2d[c].x;
				unsigned int y = objects.objects[i].bbox_2d[c].y;
				sl::uint2 point;
				point.x = x;
				point.y = y;
				bbox_2d.push_back(point);
            }
            obj.bounding_box_2d = bbox_2d;
            
			std::vector<sl::float3> bbox_3d;
            for (size_t c = 0; c < objects.objects[i].bbox_3d.size(); c++) 
            {
				float x = objects.objects[i].bbox_3d[c].x;
				float y = objects.objects[i].bbox_3d[c].y;
				float z = objects.objects[i].bbox_3d[c].z;
				sl::float3 point;
				point.x = x;
				point.y = y;
				point.z = z;
				bbox_3d.push_back(point);
            }
            obj.bounding_box = bbox_3d;
            
            std::vector<sl::float2> keypoint2;
            for (size_t j = 0; j < objects.objects[i].keypoint_2d.size(); j++)
            {
				float x = objects.objects[i].keypoint_2d[j].x;
				float y = objects.objects[i].keypoint_2d[j].y;
				sl::float2 point;
				point.x = x;
				point.y = y;
				keypoint2.push_back(point);
			}
			obj.keypoint_2d = keypoint2;
			
            std::vector<sl::float3> keypoint3;
            for (size_t j = 0; j < objects.objects[i].keypoint_3d.size(); j++)
            {
				float x = objects.objects[i].keypoint_3d[j].x;
				float y = objects.objects[i].keypoint_3d[j].y;
				float z = objects.objects[i].keypoint_3d[j].z;
				sl::float3 point;
				point.x = x;
				point.y = y;
				point.z = z;
				keypoint3.push_back(point);
			}
			obj.keypoint = keypoint3;
			
			objectsVector.push_back(obj);
		}
		
		result.object_list = objectsVector;
		ZD::saveObjects(result);
	}
}
