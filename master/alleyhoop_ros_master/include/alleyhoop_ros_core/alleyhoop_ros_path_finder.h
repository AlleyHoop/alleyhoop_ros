#ifndef  ALLEYHOOPROSPATHFINDER_H_
#define  ALLEYHOOPROSPATHFINDER_H_

#include <ros/ros.h>
#include "alleyhoop_mvc/model.h"

#include "alleyhoop_ros_utils/alleyhoop_ros_mapping.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"

#include <list>
#include <map>


namespace AlleyHoopROSCore
{

    class PathFinder : public AlleyHoopMVC::Model
    {
        public:
            PathFinder(ros::NodeHandle* _nh, AlleyHoopROSUtils::Vector3& _position, AlleyHoopROSUtils::Vector3& _nodeSizes);
            ~PathFinder();

            //path finder functions
            bool findPath(AlleyHoopROSUtils::Transform& currentTransform, AlleyHoopROSUtils::Transform& targetTransform , std::list<AlleyHoopROSUtils::Feature*>& objects, std::list<AlleyHoopROSUtils::Feature*>& road);

            static bool verboseMode;

            std::list<AlleyHoopROSUtils::Node*> path;

        protected:
            //ros
            ros::NodeHandle nh;

        private:
            //the map
            std::map<std::string, AlleyHoopROSUtils::Node*> map;
            AlleyHoopROSUtils::Node* currentNode;
            AlleyHoopROSUtils::Node* targetNode;

            //node management
            AlleyHoopROSUtils::Node* getNode(AlleyHoopROSUtils::Vector3& _position);
            AlleyHoopROSUtils::Node* getNode(std::string nodeId);
            void deleteMap();
    };

}

#endif //!  ALLEYHOOPROSPATHFINDER_H_