#!/usr/bin/env python

import roslib
roslib.load_manifest('raspi_utils')
import sys
import rospy
import picamera
import picamera.array
import time
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

# pi camera
def GetPiCameraImage():
    image = None
    with picamera.PiCamera() as camera:
        with picamera.array.PiRGBArray(camera) as stream:
            camera.capture(stream, format='bgr')
            image = stream.array
    return image

# img pub
def main(args):    
    print("starting raspi cam image publisher")

    # init ros
    pub = rospy.Publisher('raspi_cam_image_raw', Image, queue_size=10)
    rospy.init_node('raspi_camera', anonymous=True)
    rate = rospy.Rate(10)

    # create cv2 bridge
    bridge = CvBridge()

    # loop
    while not rospy.is_shutdown():
        cv_image = GetPiCameraImage()
        if(cv_image != None):
            image = bridge.cv2_to_imgmsg(cv_image, "bgr8")
            pub.publish(image)
        else:
            print("Could not get raspi camera image")
        rate.sleep()

if __name__ == '__main__':
    main(sys.argv)
    sys.exit()
