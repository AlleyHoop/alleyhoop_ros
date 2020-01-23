#ifndef ALLEYHOOPROSMAPPING_H_
#define ALLEYHOOPROSMAPPING_H_

#include <string>
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"
#include <list>

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
            bool occupied;
            bool processed;
            AlleyHoopROSUtils::Node* parent;
            std::list<AlleyHoopROSUtils::Node*> adjacentNodes;

            float heuristics;
            float distance;

            static float AlleyHoopROSUtils::Vector3 NodeSizes;

            /*!
            * \brief this function returns the cost of the node, heuristics + distance
            */
            float getNodeCost();

            /*!
            * \brief this will find nodes adjacent to the node and will fill the adjacent nodes member variable
            */
            void updateAdjacentNodes();

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
