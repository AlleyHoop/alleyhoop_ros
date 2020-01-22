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
    //* A ros pathfinder implementation of the model class from the alleyhoop_master package
    /**
    * This class is used to find a path based on features. This is done by creating map nodes and applying accessibility data to them based on features, then finding a path to a destination
    */
    class PathFinder : public AlleyHoopMVC::Model
    {
        public:
            /*!
            * \brief The constructor for the pathfinder class
            * \param _nh the nodehandle to publish data on
            * \param _position a vector of the position to start creating nodes on
            * \param _nodeSizes a vector of the sizes of a node
            */
            PathFinder(ros::NodeHandle* _nh, AlleyHoopROSUtils::Vector3& _position, AlleyHoopROSUtils::Vector3& _nodeSizes);

            /*!
            * \brief the destructor
            */
            ~PathFinder();

            /*!
            * \brief find a path from a current position to a target position
            * \param currentTransform the transform holding data of the current position and rotation
            * \param targetTransform the destrination transform
            * \param objects features on which a path CAN NOT be made
            * \param road features on which a path MUST be made
            * \TODO actually implement the function
            */ 
            bool findPath(AlleyHoopROSUtils::Transform& currentTransform, AlleyHoopROSUtils::Transform& targetTransform , std::list<AlleyHoopROSUtils::Feature*>& objects, std::list<AlleyHoopROSUtils::Feature*>& road);

            static bool verboseMode; /**< a static bool, when true more print messages will be displayed on the console*/

            std::list<AlleyHoopROSUtils::Node*> path;  /**< the path the pathfinder found */

        protected:
            //ros
            ros::NodeHandle nh; /**< the nodehandle */

        private:
            std::map<std::string, AlleyHoopROSUtils::Node*> map; /**< the map the pathfinder made based on features */
            AlleyHoopROSUtils::Node* currentNode; /**< the current position */
            AlleyHoopROSUtils::Node* targetNode; /**< the destinatinon position */

            /*!
            * \brief a utility function to get a node from a position
            * this function will do modular operations on the position based on nodeSizes given in the constructor. If the position is within the bounds of an existing node, that node will be returned.
            * \param _position the position the node is gotten from
            */
            AlleyHoopROSUtils::Node* getNode(AlleyHoopROSUtils::Vector3& _position);

            /*!
            * \brief this function will delete all map nodes
            */
            void deleteMap();
    };

}

#endif //!  ALLEYHOOPROSPATHFINDER_H_