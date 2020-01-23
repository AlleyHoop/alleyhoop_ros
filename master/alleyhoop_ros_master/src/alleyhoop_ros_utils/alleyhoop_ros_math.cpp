 #include "alleyhoop_ros_utils/alleyhoop_ros_math.h"
 #include <math.h>

namespace AlleyHoopROSUtils
{

    Vector3::Vector3()
        : x(0.0f), y(0.0f), z(0.0f)
    {

    }

    Vector3::Vector3(float _x, float _y, float _z)
        : x(0.0f), y(0.0f), z(0.0f)
    {

    }

    float Vector3::getDistance(Vector3& vec1, Vector3& vec2)
    {
        float distance = 0;
        float dis_x = abs(vec1.x - vec2.x);
        float dis_y = abs(vec1.y - vec2.y);
        float dis_z = abs(vec1.z - vec2.z);

        distance = sqrt(pow(dis_x, 2.0) + pow(dis_y, 2.0) + pow(dis_z, 2.0));
        return distance;
    }

   Transform::Transform()
   {

   }

    Transform::Transform(Vector3 _position, Vector3 _rotation, Vector3 _scale)
        : position(_position), rotation(_rotation), scale(_scale)
    {

    }

}