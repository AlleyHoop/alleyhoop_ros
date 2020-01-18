#include "alleyhoop_ros_core/alleyhoop_ros_path_finder.h"

#include <string>
#include <sstream>
#include <iostream>

namespace AlleyHoopROSCore
{
    bool PathFinder::verboseMode = false;
    float Node::NodeSizeX = 1;
    float Node::NodeSizeY = 1;
    float Node::NodeSizeZ = 1;

    Node::Node(AlleyHoopROSUtils::Vector3 _position)
        position(averagePosition(_position)), nodeId(convertPositionToNodeId(position))
    {

    };

    std::string Node::convertPositionToNodeId(AlleyHoopROSUtils::Vector3& _position)
    {
        AlleyHoopROSUtils::Vector3 pos = averagePosition(_position);
        std::string id = std::to_string(pos.x) + std::to_string(pos.y) + std::to_string(pos.z);
        return id;
    }

    AlleyHoopROSUtils::Vector3 Node::averagePosition(AlleyHoopROSUtils::Vector3& _position)
    {
        float averaged_x;
        float averaged_y;
        float averaged_z;

        if ( (_position.x % Node::NodeSizeX)/Node::NodeSizeX > 0.5f )
            averaged_x = _position.x + (Node::NodeSizeX - (_position.x % Node::NodeSizeX));
        else
            averaged_x = _position.x - (_position.x % Node::NodeSizeX);
        
        if ( (_position.y % Node::NodeSizeY)/Node::NodeSizeY > 0.5f )
            averaged_y = _position.y + (Node::NodeSizeY - (_position.y % Node::NodeSizeY));
        else
            averaged_y = _position.y - (_position.y % Node::NodeSizeY);

        if ( (_position.z % Node::NodeSizeZ)/Node::NodeSizeZ > 0.5f )
            averaged_z = _position.z + (Node::NodeSizeZ - (_position.z % Node::NodeSizeZ));
        else
            averaged_z = _position.z - (_position.z % Node::NodeSizeZ);

        AlleyHoopROSUtils::Vector3 averagedPosition(averaged_x, averaged_y, averaged_z));
        return averagedPosition;
    }

    PathFinder::PathFinder(ros::NodeHandle* _nh, AlleyHoopROSUtils::Feature& nodeFeature)
	: AlleyHoopMVC::Model(), nh(*_nh)
    {
        updateNodeFeatures(nodeFeature);
    }

    PathFinder::~PathFinder()
    {
        deleteNodes();
    }

    bool PathFinder::updateNodeFeatures(AlleyHoopROSUtils::Feature& nodeFeature)
    {
        //update node sizes based on vehicle bounding box'
        Node::NodeSizeX = nodeFeature.halfExtents.x * 2;
        Node::NodeSizeY = nodeFeature.halfExtents.y * 2;
        Node::NodeSizeZ = nodeFeature.halfExtents.z * 2;

        //update currentPosition
        currentNode = getNode(nodeFeature.transform.position);
        return true;
    }

    bool PathFinder::findPath(AlleyHoopROSUtils::Transform& currentTransform, AlleyHoopROSUtils::Transform& targetTransform, std::list<AlleyHoopROSUtils::Feature*>& objects, std::list<AlleyHoopROSUtils::Feature*>& road)
    {
        
        return true;
    }


    Node* PathFinder::getNode(AlleyHoopROSUtils::Vector3& _position)
    {
        //return if node not already existing
        std::string nodeId = Node::convertPositionToNodeId(_position);
        for (nodes.find(nodeId) != nodes.end())
        {
            return *(nodes.find(nodeId)->second);
        }

        //create new node and save if not existing
        Node* node = new Node(_position);
        nodes[node->nodeId] = node;
        return node;
    }

    void PathFinder::deleteNodes()
    {
        for (std::map<std::string, Node*>::iterator node_iter = nodes.begin(); node_iter != nodes.end(); node_iter++)
        {
            if(*(nodes->second) != nullptr)
                delete *(nodes->second);
        }

        nodes.clear();
        path.clear(); 
    }

    

}