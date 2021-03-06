#!/usr/bin/env python
import roslib
roslib.load_manifest('alleyhoop_monitor')
import rospy
import tf

rospy.init_node('alleyhoop_frame_broadcaster')
br_odom_frame = tf.TransformBroadcaster()
rate = rospy.Rate(10.0)
while not rospy.is_shutdown():
    br_odom_frame.sendTransform((0.0, 0.0, 0.0),
                    (0.0, 0.0, 0.0, 1.0),
                     rospy.Time.now(),
                     "/base_link",
                     "/odom")
    rate.sleep()
