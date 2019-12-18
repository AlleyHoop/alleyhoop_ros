#!/usr/bin/env python
import roslib
roslib.load_manifest('test_pkg')
import rospy
import tf

rospy.init_node('vehicle_tf_broadcaster')
br = tf.TransformBroadcaster()
rate = rospy.Rate(10.0)
while not rospy.is_shutdown():
    br.sendTransform((0.0, 0.0, 0.0),
                     (0.0, 0.0, 0.0, 1.0),
                     rospy.Time.now(),
                     "world",
                     "laser")
