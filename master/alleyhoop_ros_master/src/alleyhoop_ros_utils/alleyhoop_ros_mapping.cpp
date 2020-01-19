#include "alleyhoop_ros_utils/alleyhoop_ros_mapping.h"
#include <bits/stdc++.h>    //required for fmod operation 

namespace AlleyHoopROSUtils
{

    float Node::NodeSizeX = 1;
    float Node::NodeSizeY = 1;
    float Node::NodeSizeZ = 1;

    Node::Node(AlleyHoopROSUtils::Vector3 _position)
        : position(averagePosition(_position)), nodeId(convertPositionToNodeId(position))
    {

    }

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

        if ( std::fmod(_position.x, Node::NodeSizeX)/Node::NodeSizeX > 0.5f )
            averaged_x = _position.x + (Node::NodeSizeX - (_position.x , Node::NodeSizeX));
        else
            averaged_x = _position.x - std::fmod(_position.x , Node::NodeSizeX);
        
        if (std::fmod(_position.y , Node::NodeSizeY)/Node::NodeSizeY > 0.5f )
            averaged_y = _position.y + (Node::NodeSizeY - (_position.y , Node::NodeSizeY));
        else
            averaged_y = _position.y - std::fmod(_position.y , Node::NodeSizeY);

        if ( std::fmod(_position.z, Node::NodeSizeZ)/Node::NodeSizeZ > 0.5f )
            averaged_z = _position.z + (Node::NodeSizeZ - (_position.z , Node::NodeSizeZ));
        else
            averaged_z = _position.z - std::fmod(_position.z , Node::NodeSizeZ);

        AlleyHoopROSUtils::Vector3 averagedPosition(averaged_x, averaged_y, averaged_z);
        return averagedPosition;
    }

     void Node::updateNodeSizes(Vector3& nodeSizes)
     {
        Node::NodeSizeX = nodeSizes.x;
        Node::NodeSizeY = nodeSizes.y;
        Node::NodeSizeZ = nodeSizes.z;
     }

}