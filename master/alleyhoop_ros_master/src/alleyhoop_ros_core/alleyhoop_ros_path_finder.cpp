#include "alleyhoop_ros_core/alleyhoop_ros_path_finder.h"

#include <string>
#include <iostream>

namespace AlleyHoopROSCore
{
    bool PathFinder::verboseMode = false;

    PathFinder::PathFinder(ros::NodeHandle* _nh, AlleyHoopROSUtils::Vector3& _position, AlleyHoopROSUtils::Vector3& _nodeSizes)
	: AlleyHoopMVC::Model(), nh(*_nh)
    {
        AlleyHoopROSUtils::Node::updateNodeSizes(_nodeSizes);
        currentNode = getNode(_position);
    }

    PathFinder::~PathFinder()
    {
        deleteMap();
    }

    bool PathFinder::findPath(AlleyHoopROSUtils::Transform& currentTransform, AlleyHoopROSUtils::Transform& targetTransform, std::list<AlleyHoopROSUtils::Feature*>& objects, std::list<AlleyHoopROSUtils::Feature*>& road)
    {
        return true;
    }


    AlleyHoopROSUtils::Node* PathFinder::getNode(AlleyHoopROSUtils::Vector3& _position)
    {
        //return node if already existing
        std::string nodeId = AlleyHoopROSUtils::Node::convertPositionToNodeId(_position);
        for (std::map<std::string, AlleyHoopROSUtils::Node*>::iterator node_iter = map.begin(); node_iter != map.end(); node_iter++)
        {
            if(node_iter->first == nodeId)
                if(node_iter->second != nullptr)
                    return node_iter->second;
                else
                    break;
        }

        //create new node and save if not existing
        AlleyHoopROSUtils::Node* node = new AlleyHoopROSUtils::Node(_position);
        map[node->nodeId] = node;
        return node;
    }

    void PathFinder::deleteMap()
    {
        for (std::map<std::string, AlleyHoopROSUtils::Node*>::iterator node_iter = map.begin(); node_iter != map.end(); node_iter++)
        {
            if(node_iter->second != nullptr)
                delete node_iter->second;
        }

        map.clear();
        path.clear(); 
    }

    

}