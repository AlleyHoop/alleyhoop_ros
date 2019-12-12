#!/usr/bin/env python

import roslib
roslib.load_manifest('raspi_utils')
import sys
import rospy
import picamera
import picamera.array
import time
import cv2
import io
import numpy as np
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

# pi camera
def GetPiCameraImageAsCvImage():
    image = None
    with picamera.PiCamera() as camera:
        with picamera.array.PiRGBArray(camera) as stream:
            camera.capture(stream, format='bgr')
            image = stream.array

    return image

def GetPiCameraImageAsCvImageJpegFormat():
    stream = io.BytesIO()
    with picamera.PiCamera() as camera:
        camera.capture(stream, format='jpeg')
    
    data = np.fromstring(stream.getvalue(), dtype=np.uint8)
    image = cv2.imdecode(data, 1)
    return image

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
        cv_image = GetPiCameraImageAsCvImage()
        image = bridge.cv2_to_imgmsg(cv_image, "bgr8")
        pub.publish(image)
        rate.sleep()

if __name__ == '__main__':
    main(sys.argv)
    sys.exit()
