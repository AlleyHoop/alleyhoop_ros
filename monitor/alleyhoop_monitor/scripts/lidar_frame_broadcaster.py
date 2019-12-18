#!/usr/bin/env python
import roslib
roslib.load_manifest('alleyhoop_monitor')
import rospy
import tf

rospy.init_node('lidar_tf_broadcaster')
br = tf.TransformBroadcaster()
rate = rospy.Rate(10.0)
while not rospy.is_shutdown():
    br.sendTransform((0.0, 0.0, 0.0),
                     (0.0, 0.0, 0.0, 1.0),
                     rospy.Time.now(),
                     "base_link",
                     "laser")
