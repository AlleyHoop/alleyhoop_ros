#ifndef  ALLEYHOOPROSPATHFINDER_H_
#define  ALLEYHOOPROSPATHFINDER_H_

#include <ros/ros.h>
#include "alleyhoop_mvc/model.h"

#include "alleyhoop_ros_utils/alleyhoop_ros_mapping.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"
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
            * \todo actually implement the function
            */ 
            bool findPath(AlleyHoopROSUtils::Transform& currentTransform, AlleyHoopROSUtils::Transform& targetTransform , std::list<AlleyHoopROSUtils::Feature*>& objects, std::list<AlleyHoopROSUtils::Feature*>& road);

            static bool verboseMode; /**< a static bool, when true more print messages will be displayed on the console*/

            std::list<AlleyHoopROSUtils::Node*> path;  /**< the path the pathfinder found */

        protected:
            //ros
            ros::NodeHandle nh; /**< the nodehandle */

        private:
            std::map<std::string, AlleyHoopROSUtils::Node*> map; /**< the map the pathfinder made based on features */
            AlleyHoopROSUtils::Node* referenceNode; /**< node to reference from */
            std::list<AlleyHoopROSUtils::Node*> currentNodes; /**< the current nodes occupied by the vehicle */
            AlleyHoopROSUtils::Node* targetNode; /**< the destinatinon position */

            /*!
            * \brief a utility function to convert features into nodes
            * this function will pass the convertion of a node to the function getNodes where after it will set the occupancy values of the node
            * \param features these are the features to be converted
            */
            void instantiateNodesFromFeatures(std::list<AlleyHoopROSUtils::Feature*>& features);

            /*!
            * \brief a utility function to get and or create a node from a position
            * this function will do modular operations on the position based on nodeSizes given in the constructor. If the position is within the bounds of an existing node, that node will be returned.
            * Note that a new node will be created if not already existing
            * \param _position the position the node is gotten from
            */
            AlleyHoopROSUtils::Node* getNode(AlleyHoopROSUtils::Vector3& _position);

            /*!
            * \brief a utility function to get a node from a node id
            * Unlike the other getNode function, this one will not create a new node
            * \param _nodeId the id of the node
            */
            AlleyHoopROSUtils::Node* getNode(std::string _nodeId);

            /*!
            * \brief a utility function to get a node from a node id
            * Unlike the other getNode function, this one will not create a new node
            * \param _transform the transform of the node
            * \param extents the lengths of each side of the object to translate to nodes 
            */
            std::list<AlleyHoopROSUtils::Node*> getNodes(AlleyHoopROSUtils::Transform& _transform, AlleyHoopROSUtils::Vector3& extents);

            /*!
            * \brief a utility function to get a node from a given list with id. Will return a nullptr when no node is found.
            * \param nodeList the list to find the node in
            * \param _nodeId the id of the node to be found
            */
            AlleyHoopROSUtils::Node* getNodeInList(std::list<AlleyHoopROSUtils::Node*>& nodeList, std::string _nodeId);

            /*!
            * \brief a utility function to fill the adjacentNodes member of a given node
            * \todo implement the logic for this function so that all adjacent nodes, with a unit of nodeSize are added into the adjacent nodes list in the node
            * \param _node the node to find adjacentNode for
            */
            void updateAdjacentNodes(AlleyHoopROSUtils::Node* _node);

            /*!
            * \brief this function will delete all map nodes
            */
            void deleteMap();
    };

}

#endif //!  ALLEYHOOPROSPATHFINDER_H_