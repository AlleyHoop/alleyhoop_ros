#ifndef ALLEYHOOPROSFEATURE_H_
#define ALLEYHOOPROSFEATURE_H_

#include <ros/ros.h>
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"
#include <string>

namespace AlleyHoopROSUtils
{
    enum FeatureTypes {None=0, StaticObject=1, MovingObject=2};

    class Feature
    {
        public:
            Feature(int type);
            ~Feature() = default;
            AlleyHoopROSUtils::Transform transform;
            AlleyHoopROSUtils::Vector3 halfExtents;
            int featureType;
            std::string label_name;
    };

}

#endif //!ALLEYHOOPROSFEATURE_H_
