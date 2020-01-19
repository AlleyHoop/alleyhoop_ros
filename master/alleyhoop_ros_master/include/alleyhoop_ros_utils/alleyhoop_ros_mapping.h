#ifndef ALLEYHOOPROSMAPPING_H_
#define ALLEYHOOPROSMAPPING_H_

#include <string>
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"

namespace AlleyHoopROSUtils
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
            static void updateNodeSizes(Vector3& nodeSizes);
            
    };

}

#endif //!ALLEYHOOPROSMAPPING_H_
