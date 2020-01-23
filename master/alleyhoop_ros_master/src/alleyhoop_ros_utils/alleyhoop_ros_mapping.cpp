#include "alleyhoop_ros_utils/alleyhoop_ros_mapping.h"
#include <bits/stdc++.h>    //required for fmod operation 

namespace AlleyHoopROSUtils
{

    AlleyHoopROSUtils::Vector3 Node::NodeSizes;

    Node::Node(AlleyHoopROSUtils::Vector3 _position)
        : position(averagePosition(_position)), nodeId(convertPositionToNodeId(position)), walkable(false), occupied(false), processed(false), distance(0), heuristics(0), parent(nullptr)
    {

    }

    float Node::getNodeCost()
    {
        return distance + heuristics;
    }

    std::string Node::convertPositionToNodeId(AlleyHoopROSUtils::Vector3& _position)
    {
        AlleyHoopROSUtils::Vector3 pos = averagePosition(_position);
        std::string id = std::to_string(pos.x) + "|" + std::to_string(pos.y) + "|" + std::to_string(pos.z);
        return id;
    }

    AlleyHoopROSUtils::Vector3 Node::averagePosition(AlleyHoopROSUtils::Vector3& _position)
    {
        float averaged_x;
        float averaged_y;
        float averaged_z;

        if ( std::fmod(_position.x, Node::NodeSizes.x)/Node::NodeSizes.x > 0.5f )
            averaged_x = _position.x + (Node::NodeSizes.x - (_position.x , Node::NodeSizes.x));
        else
            averaged_x = _position.x - std::fmod(_position.x , Node::NodeSizes.x);
        
        if (std::fmod(_position.y , Node::NodeSizes.y)/Node::NodeSizes.y > 0.5f )
            averaged_y = _position.y + (Node::NodeSizes.y - (_position.y , Node::NodeSizes.y));
        else
            averaged_y = _position.y - std::fmod(_position.y , Node::NodeSizes.y);

        if ( std::fmod(_position.z, Node::NodeSizes.z)/Node::NodeSizes.z > 0.5f )
            averaged_z = _position.z + (Node::NodeSizes.z - (_position.z , Node::NodeSizes.z));
        else
            averaged_z = _position.z - std::fmod(_position.z , Node::NodeSizes.z);

        AlleyHoopROSUtils::Vector3 averagedPosition(averaged_x, averaged_y, averaged_z);
        return averagedPosition;
    }

     void Node::updateNodeSizes(Vector3& nodeSizes)
     {
        Node::NodeSizes.x = nodeSizes.x;
        Node::NodeSizes.y = nodeSizes.y;
        Node::NodeSizes.z = nodeSizes.z;
     }

}