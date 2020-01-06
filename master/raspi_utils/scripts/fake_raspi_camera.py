#!/usr/bin/env python

import roslib
roslib.load_manifest('raspi_utils')
import sys
import rospy
import time
import cv2
import io
import numpy as np
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

# img pub
def main(args):
    print("starting raspi cam image publisher on topic /raspi_camera/image_raw")

    # init ros
    rospy.init_node('raspi_camera', anonymous=True)
    pub = rospy.Publisher('/raspi_camera/image_raw', Image, queue_size=10)
    rate = rospy.Rate(10)

    # create cv2 bridge
    bridge = CvBridge()

    # loop
    while not rospy.is_shutdown():
        