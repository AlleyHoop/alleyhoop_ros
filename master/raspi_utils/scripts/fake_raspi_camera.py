#!/usr/bin/env python

import roslib
roslib.load_manifest('raspi_utils')
import sys
import rospy
import time
import cv2
import numpy as np
import os
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

# img pub
def main(args):
    print("starting fake raspi cam image publisher on topic /raspi_camera/image_raw")

    # init ros
    rospy.init_node('raspi_camera', anonymous=True)
    pub = rospy.Publisher('/raspi_camera/image_raw', Image, queue_size=10)
    rate = rospy.Rate(10)

    # create cv2 bridge
    bridge = CvBridge()

    pth = os.path.join(os.getcwd(), 'anwbw760.jpeg')
    print("reading image from " + pth)

    # loop
    while not rospy.is_shutdown():
        cv_image = cv2.imread(pth)
        image = bridge.cv2_to_imgmsg(cv_image, "bgr8")
        pub.publish(image)
        rate.sleep()
    

if __name__ == '__main__':
    main(sys.argv)
    sys.exit()