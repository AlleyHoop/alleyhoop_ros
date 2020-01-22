#ifndef ALLEYHOOPROSMAPPING_H_
#define ALLEYHOOPROSMAPPING_H_

#include <string>
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"

namespace AlleyHoopROSUtils
{
    //* A utility class for positioning
    /**
    */

    class Node
    {
        public:
            /*!
            * \brief A node used for mapping and pathfinding
            * \param _position a vector of the position of the node
            */
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

            /*!
            * \brief get a node id from a given position
            * This function will call averagePosition to get an actual node position
            * \param _position a vector of the position of the node
            */
            static std::string convertPositionToNodeId(AlleyHoopROSUtils::Vector3& _position);

            /*!
            * \brief do modular operations on position and get an averaged position on which a node can be based on
            * \param _position a vector of the position of the node
            */
            static AlleyHoopROSUtils::Vector3 averagePosition(AlleyHoopROSUtils::Vector3& _position);

            /*!
            * \brief a utility function to set the sizes of a node
            * \param nodeSizes a vector of the sizes of a node
            */
            static void updateNodeSizes(Vector3& nodeSizes);
            
    };

}

#endif //!ALLEYHOOPROSMAPPING_H_
