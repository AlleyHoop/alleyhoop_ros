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
        referenceNode = getNode(_position);
        std::cout << "created pathfinder" << std::endl;
    }

    PathFinder::~PathFinder()
    {
        deleteMap();
    }

    bool PathFinder::findPath(AlleyHoopROSUtils::Transform& currentTransform, AlleyHoopROSUtils::Transform& targetTransform, std::list<AlleyHoopROSUtils::Feature*>& objects, std::list<AlleyHoopROSUtils::Feature*>& road)
    {
        //set current node \todo base the extents on the vehicles features
        currentNodes = getNodes(currentTransform, AlleyHoopROSUtils::NodeSizes);
        for(std::list<AlleyHoopROSUtils::Node*>::iterator node_iter = currentNodes.begin(); node_iter != currentNodes.end(); node_iter++)
        {
            AlleyHoopROSUtils::Feature* newNode = (*node_iter);
            newNode->walkable = true;
        }

        //instantiate nodes
        instantiateNodesFromFeatures(objects);
        instantiateNodesFromFeatures(road);

        //create opened & closed list
        std::list<AlleyHoopROSUtils::Node*> openList;
        std::list<AlleyHoopROSUtils::Node*> closedList;
        AlleyHoopROSUtils::Node* processNode = getNode(currentTransform.position);
        AlleyHoopROSUtils::Node* lastNode = getNode(targetTransform.position);

        //set the node to start with
        openList.push_back(processNode);

        //calculate estimated distance 
        float estimated_distance = AlleyHoopROSUtils::Vector3::getDistance( processNode->position, lastNode->position );

        //clear processed nodes
        for(std::map<std::string, AlleyHoopROSUtils::Node*>::iterator node_iter = map.begin(); node_iter != map.end(); node_iter++)
        {
            (*node_iter)->processed = false;
        }

        //find path
        while(true)
        {
            //take node with lowest cost(distance + heuristic) from opened list
            float lowest_cost = estimated_distance * 3;
            std::string nodeWithLowestCost = "none";
            for(std::list<AlleyHoopROSUtils::Node*>::iterator node_iter = openList.begin(); node_iter != openList.end(); node_iter++)
            {
                AlleyHoopROSUtils::Node* node = (*node_iter);
                if(node->getNodeCost() < lowest_cost)
                {
                    lowest_cost = node->getNodeCost();
                    nodeWithLowestCost = node->nodeId;
                }
            }

            //set node to process
            processNode = getNode(nodeWithLowestCost);
            if(processNode == nullptr)
            {
                break;
            }
            openList.remove(processNode);

            //exit if node being processed is the destination node
            if(processNode->nodeId == lastNode->nodeId)
            {
                break;
            }

            //add node being processed to closed list
            closedList.push_back(processNode);
            processNode->processed = true;

            //iterate through processed node adjacent nodes
            updateAdjacentNodes(processNode);
            for (std::list<AlleyHoopROSUtils::Node*>::iterator adj_node_iter = processNode->adjacentNodes.begin(); adj_node_iter != processNode->adjacentNodes.end(); adj_node_iter++)
            {
                //ingnore non walkable nodes or already processed nodes
                if(!adj_node_iter->walkable || adj_node_iter->occupied || adj_node_iter->processed)
                {
                    continue;
                }

                //set the heuritic = (sqrt of (dx^2 + dy^2 + dz^2)), distance value, and path if not in open list yet
                AlleyHoopROSUtils::Node* adj_node = getNodeInList(openList, adj_node_iter->nodeId);
                if(adj_node == nullptr)
                {
                    adj_node = (*adj_node_iter);
                
                    //set values
                    adj_node->parent = processNode;
                    adj_node->distance = processNode->distance + 1;
                    adj_node->heuristics = AlleyHoopROSUtils::Vector3::getDistance( adj_node->position, lastNode->position );

                    //add to open list
                    openList.push_back(adj_node);
                    continue;
                }

                //change distance and path if in open list
                if(adj_node->distance < processNode->distance)
                {
                    adj_node->parent = processNode;
                    adj_node->distance = processNode->distance + 1;
                }
            }
        }

        //exit if not found path
        if(processNode == nullptr)
        {
            if(verbose_mode) std::cout << "did not find a path" << std::endl
            return false;
        }

        //set the path
        AlleyHoopROSUtils::Node* next_node = processNode;
        while(next_node != nullptr)
        {
            path.push_back(next_node);
            next_node = next_node->parent;
        }
        if(verbose_mode) std::cout << "succesfully found a path" << std::endl

        return true;
    }

    void PathFinder::instantiateNodesFromFeatures(std::list<AlleyHoopROSUtils::Feature*>& features)
    {
        for(std::list<AlleyHoopROSUtils::Feature*>::iterator feature_iter = features.begin(); feature_iter != features.end(); feature_iter++)
        {
            AlleyHoopROSUtils::Feature* feature = (*feature_iter);
            std::list<AlleyHoopROSUtils::Node*> _nodes = getNodes(feature->transform, feature->extents);

            for(std::list<AlleyHoopROSUtils::Node*>::iterator node_iter = _nodes.begin(); node_iter != _nodes.end(); node_iter++)
            {
                AlleyHoopROSUtils::Feature* newNode = (*node_iter);
        
                //check type of feature and set feature types
                if(feature->featureType == AlleyHoopROSUtils::FeatureTypes::Object)
                {
                    newNode->occupied = true;
                }

                if(feature->featureType == AlleyHoopROSUtils::FeatureTypes::MovingObject)
                {
                    newNode->occupied = true;
                }

                if(feature->featureType == AlleyHoopROSUtils::FeatureTypes::Road)
                {
                    newNode->walkable = true;
                }

            }
        }
    }

    std::list<AlleyHoopROSUtils::Node*> PathFinder::getNodes(AlleyHoopROSUtils::Transform& _transform, AlleyHoopROSUtils::Vector3& extents)
    {
        //to return list
        std::list<AlleyHoopROSUtils::Node*> _nodes;

        //get bounds
        float start_x = transform.position.x - (extents.x/2.0f);
        float start_y = transform.position.y - (extents.y/2.0f);
        float start_z = transform.position.z - (extents.z/2.0f);
        float end_x = transform.position.x + (extents.x/2.0f);
        float end_y = transform.position.y + (extents.y/2.0f);
        float end_z = transform.position.z + (extent.z/2.0f);

        //\todo apply rotation reference from reference node
        // start_x *=
        // start_y *=
        // start_z *= 
        // end_x *=
        // end_y *=
        // end_z *= 

        //interpolate new nodes between bounds
        while(start_x < end_x)
        {
            while(start_y < end_y)
            {
                while(start_z < end_z)
                {        
                    AlleyHoopROSUtils::Vector3 position(start_x, start_y, start_z);

                    //create node note thats the node pointer is also saved in map
                    _nodes.push_back(getNode(position));

                    start_z += AlleyHoopROSUtils::NodeSizes.x;
                }
                start_y+= AlleyHoopROSUtils::NodeSizes.y;
            }
            start_x+= AlleyHoopROSUtils::NodeSizes.z;
        }

        return _nodes;
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
        if(verboseMode) std::cout << " Pathfinder: created node " << node->nodeId << std::endl;
        return node;
    }

    AlleyHoopROSUtils::Node* PathFinder::getNode(std::string _nodeId)
    {
        //return node only if already existing
        for (std::map<std::string, AlleyHoopROSUtils::Node*>::iterator node_iter = map.begin(); node_iter != map.end(); node_iter++)
        {
            if(node_iter->first == nodeId)
                if(node_iter->second != nullptr)
                    return node_iter->second;
                else
                    break;
        }

        //do not create a new node
        return nullptr;
    }

    AlleyHoopROSUtils::Node* PathFinder::getNodeInList(std::list<AlleyHoopROSUtils::Node*>& nodeList, std::string _nodeId)
    {
        for (std::list<AlleyHoopROSUtils::Node*>::iterator node_iter = nodeList.begin(); node_iter != nodeList.end(); node_iter++)
        {
            if(_nodeId == (*node_iter)->nodeId)
                return (*node_iter);
        }

        return nullptr;
    }

    void PathFinder::updateAdjacentNodes(AlleyHoopROSUtils::Node* _node)
    {
        
    }

    void PathFinder::deleteMap()
    {
        for (std::map<std::string, AlleyHoopROSUtils::Node*>::iterator node_iter = map.begin(); node_iter != map.end(); node_iter++)
        {
            if(node_iter->second != nullptr)
            {
                if(verboseMode) std::cout << " Pathfinder: deleted node " << node_iter->second->nodeId << std::endl;
                delete node_iter->second;
            }
        }

        map.clear();
        path.clear(); 
    }

    

}