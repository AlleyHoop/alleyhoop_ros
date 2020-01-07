#ifndef ALLEYHOOPROSFEATURE_H_
#define ALLEYHOOPROSFEATURE_H_

#include <ros/ros.h>
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"

namespace AlleyHoopROSUtils
{
    enum FeatureTypes {None=0, StaticObject=1, SpecificObject=2, MovingObject=3};

    class AlleyHoopFeature
    {
        public:
            AlleyHoopFeature(int type);
            ~AlleyHoopFeature() = default;
            AlleyHoopROSUtils::AlleyHoopTransform transform;
            int featureType;
    };

}

#endif //!ALLEYHOOPROSFEATURE_H_
