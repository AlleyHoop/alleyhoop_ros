#ifndef  ALLEYHOOPROSPATHFINDER_H_
#define  ALLEYHOOPROSPATHFINDER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/model.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/PointCloud2.h>
#include <list>
#include <map>


namespace AlleyHoopROSCore
{
    class Node
    {
        public:
            Node(AlleyHoopROSUtils::Vector3 _position);
            ~Node() = default;
            const std::string nodeId;

            AlleyHoopROSUtils::Vector3 position;
            bool walkable;
            bool processed;

            float heuristics;
            float distance;

            static float NodeSizeX;
            static float NodeSizeY;
            static float NodeSizeZ;

            static std::string convertPositionToNodeId(AlleyHoopROSUtils::Vector3& _position);
            static AlleyHoopROSUtils::Vector3 averagePosition(AlleyHoopROSUtils::Vector3& _position);
    }

    class PathFinder : public AlleyHoopMVC::Model
    {
        public:
            PathFinder(ros::NodeHandle* _nh, AlleyHoopROSUtils::Feature& nodeFeature);
            ~PathFinder();

            //sync with vehicle
            bool updateNodeFeatures(AlleyHoopROSUtils::Feature& nodeFeature);

            //path finder functions
            bool findPath(AlleyHoopROSUtils::Transform& currentTransform, AlleyHoopROSUtils::Transform targetTransform& , std::list<AlleyHoopROSUtils::Feature*>& objects, std::list<AlleyHoopROSUtils::Feature*>& road);

            static bool verboseMode;

            std::list<Node*> path;

        protected:
            //ros
            ros::NodeHandle nh;

        private:
            //the map
            std::map<std::string, Node*> nodes;
            Node* currentNode;
            Node* targetNode;

            //node management
            Node* getNode(AlleyHoopROSUtils::Vector3& _position);
            Node* getNode(std::string nodeId);
            void deleteNodes();
    };

}

#endif //!  ALLEYHOOPROSPATHFINDER_H_