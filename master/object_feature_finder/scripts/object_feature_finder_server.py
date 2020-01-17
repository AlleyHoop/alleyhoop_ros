#!/usr/bin/env python

# ros required libs
import roslib
roslib.load_manifest('object_feature_finder')
import rospy

# libs for processing
import sys
import time
import cv2
import numpy as np
import os

# needed for ros service
from cv_bridge import CvBridge, CvBridgeError
from alleyhoop_ros_msgs.srv import FindFeaturesOnImage,FindFeaturesOnImageResponse

# needed for yolo
from darknet_ros_msgs.msg import BoundingBoxes,BoundingBox
currentBoundingBoxes = None
newBoundingBoxes = False

def boundingBoxesCallback(data):
    currentBoundingBoxes = data
    newBoundingBoxes = True

# the function
def findFeatures(request):
    # get the image
    bridge = CvBridge()
    img = bridge.imgmsg_to_cv2(request.image, "bgr8")

    # setup features
    response = FindFeaturesOnImageResponse()
    if(newBoundingBoxes):
        response.step = 4

        # write response
        for bb in currentBoundingBoxes.bounding_boxes:
            response.features.append(bb.xmin)
            response.features.append(bb.ymin)
            response.features.append(bb.xmax)
            response.features.append(bb.ymax)
    else:
        response.step = 0

    # return features
    return response


def main(args):
    # init ros
    service_name = "object_feature_finder"
    print("starting object feature finder service at " + service_name)
    rospy.init_node(service_name + '_server')

    # init bounding box subscriber
    boundingboxes_sub = rospy.Subscriber("yolo_feature_finder_bounding_boxes_sub", BoundingBoxes, boundingBoxesCallback)

    # init service
    service = rospy.Service(service_name, FindFeaturesOnImage, findFeatures)

    # process requests
    print "Ready to find features of an image."
    rospy.spin()


if __name__ == '__main__':
    main(sys.argv)
    sys.exit()