#ifndef  ALLEYHOOPROSFEATUREFINDER_H_
#define  ALLEYHOOPROSFEATUREFINDER_H_


#include <ros/ros.h>

#include "alleyhoop_mvc/model.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/PointCloud2.h>
#include <list>



namespace AlleyHoopROSCore
{
    //* A ros feature finder implementation of the model class from the alleyhoop_master package
    /**
    * This class is used to retrieve feature from a image. This concerns the position of objects on an image including depth data
    */
    class FeatureFinder : public AlleyHoopMVC::Model
    {
        public:
            /*!
            * \brief The constructor for the featurefinder class
            * \param _nh the nodehandle to publish data on
            */
            FeatureFinder(ros::NodeHandle* _nh);

            /*!
            * \brief a default destructor
            */
            ~FeatureFinder() = default;

            /*!
            * \brief a function to find objects on an image.
            * This function will use ros services to detect features. This means that the actual detection can be implemented in various ways and is external from this package
            * The function will return true when it has succesfully retrieved data
            * \param features is a list in which features will be added. 
            * \param imagePtr is the image from which features will be extracted
            */

            bool findObjectsOnImage(std::list<AlleyHoopROSUtils::Feature*>& features, cv_bridge::CvImagePtr& imagePtr);
            /*!
            * \brief a function to find traffic rules and signs on an image.
            * This function will use ros services to detect features. This means that the actual detection can be implemented in various ways and is external from this package
            * The function will return true when it has succesfully retrieved data
            * \param features is a list in which features will be added. 
            * \param imagePtr is the image from which features will be extracted
            */
            bool findTrafficRulesOnImage(std::list<AlleyHoopROSUtils::Feature*>& features, cv_bridge::CvImagePtr& imagePtr);

            /*!
            * \brief a function to find a road on an image.
            * This function will use ros services to detect features. This means that the actual detection can be implemented in various ways and is external from this package
            * The function will return true when it has succesfully retrieved data
            * \param features is a list in which features will be added. 
            * \param imagePtr is the image from which features will be extracted
            */
            bool findRoadOnImage(std::list<AlleyHoopROSUtils::Feature*>& features, cv_bridge::CvImagePtr& imagePtr);

            /*!
            * \brief this function will process depth data of features by finding there distance using pointcloud data.
            * This is an internal function of the package. For accurate results it is required that features passed in the parameters are from an image coming from the same camera from which the poincloud data is extracted.
            * \param features is a list of features on which depth data will be added pased on pointcloud data
            * \param pcl is the image from which pointcloud data will be extracted
            * \todo actually implement the function
            */
            bool processDepthDataOnFeatures(std::list<AlleyHoopROSUtils::Feature*>& features, sensor_msgs::PointCloud2& pcl);

            static bool verboseMode; /**< a static bool, when true more print messages will be displayed on the console*/

        protected:
            //ros
            ros::NodeHandle nh; /**< the nodehandle on which to initalise the service clients */

            //finder clients
            ros::ServiceClient traffic_rules_feature_finder_client; /**< the service client for retrieving data when the function findTrafficRulesOnImage is called*/
            ros::ServiceClient road_feature_finder_client; /**< the service client for retrieving data when the function findRoadOnImage is called*/
            ros::ServiceClient object_feature_finder_client; /**< the service client for retrieving data when the function findObjectsOnImage is called*/
    };

}

#endif //!  ALLEYHOOPROSFEATUREFINDER_H_