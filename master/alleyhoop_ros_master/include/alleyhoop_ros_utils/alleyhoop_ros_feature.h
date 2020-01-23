#ifndef ALLEYHOOPROSFEATURE_H_
#define ALLEYHOOPROSFEATURE_H_


#include <ros/ros.h>
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"
#include <string>

namespace AlleyHoopROSUtils
{
    enum FeatureTypes {None=0, Object=1, MovingObject=2, Road=3};

    //* A utility class for saving features and passing on relevant information
    /**
    * This class has a transform in which postional values are to be saved
    * This class has a vector3 on which the bouding lines of an object are defined
    */
   
    class Feature
    {
        public:
            /*!
            * \brief The constructor for the feature class
            * \param type an integer stating which type of object the feature is representing
            */ 
            Feature(int type);

            /*!
            * \brief The destructor
            */ 
            virtual ~Feature();


            AlleyHoopROSUtils::Transform transform; /**< the transform of the feature */
            AlleyHoopROSUtils::Vector3 extents; /**< the lengths of each side (x, y, z) */
            int featureType; /**< the type of feature this is */
            std::string label_name; /**< the label name, such us bike, car, person... */
    };

}

#endif //!ALLEYHOOPROSFEATURE_H_
