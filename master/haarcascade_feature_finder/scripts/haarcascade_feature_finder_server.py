#!/usr/bin/env python

# ros required libs
import roslib
roslib.load_manifest('haarcascade_feature_finder')
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

# load in cascades
face_cascade = cv2.CascadeClassifier('../config/haarcascade_eye')
eye_cascade = cv2.CascadeClassifier('../config/haarcascade_frontalce_default')

# the function
def findFeatures(request):
    # get the image
    bridge = CvBridge()
    img = bridge.imgmsg_to_cv2(request.image, "bgr8")

    # convert image
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # find cascades
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    # setup features
    response = FindFeaturesOnImageResponse()
    response.step = 4
    # write response and draw features
    for (x, y, w, h) in faces:
        # write response
        response.features.append(x)
        response.features.append(y)
        response.features.append(w)
        response.features.append(h)

        # drawing rectangle
        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)

        # region of interest only in the face since it is eyes
        roi_gray = gray[y:y + h, x:x + w]
        roi_color = img[y:y + h, x:x + w]
        eyes = eye_cascade.detectMultiScale(roi_gray)
        for (ex, ey, ew, eh) in eyes:
            cv2.rectangle(roi_color, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)

    # show features
    # cv2.imshow('img', img)
    # cv2.waitKey(0)

    # return features
    return response


def main(args):
    # init ros
    service_name = "haarcascade_feature_finder"
    print("starting haarcascade feature finder service at " + service_name)
    rospy.init_node(service_name + '_server')

    # init service
    s = rospy.Service(service_name, FindFeaturesOnImage, findFeatures)

    # process requests
    print "Ready to find features of an image."
    rospy.spin()


if __name__ == '__main__':
    main(sys.argv)
    sys.exit()