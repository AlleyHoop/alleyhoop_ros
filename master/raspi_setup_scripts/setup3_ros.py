#!/usr/bin/env python
import sys
import subprocess
import re
import os
import glob
import getpass

# exit if no sudo
if os.geteuid() != 0:
    print("please run with sudo!!!")
    sys.exit()

# list with logs
log = []

# print log list
def print_log():
    print("\n ROS installation script Log and Error list:")
    if not log:
        print("No entries in script log found.")
    else:
        count = 0
        for entry in log:
            count += 1
            print("\n"+str(count)+") "+entry)

# ROS args
pth_ros_distribution = "/opt/ros/kinetic/setup.bash"
arg_ros_sources = 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
arg_keyp1 = 'hkp://keyserver.ubuntu.com:80'
arg_keyp2 = 'C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654'
arg_ros_distribution = "ros-kinetic-desktop-full"

#install ros
if not (os.path.exists(pth_ros_distribution)):
    # setup sources
    subprocess.call(["sh", "-c", arg_ros_sources])
    subprocess.call(["apt-key", "adv", "--keyserver", arg_keyp1, '--recv-key', arg_keyp2])
    subprocess.call(["apt-get", "update", "-y"])
    log.append("setup sources for " + arg_ros_distribution)

    # install ros
    subprocess.call(["apt-get", "install", arg_ros_distribution, "-y"])
    subprocess.call(["apt", "install", "python-rosdep", "-y"])
    subprocess.call(["rosdep", "init"])
    subprocess.call(["rosdep", "update"])
    log.append("installed " + arg_ros_distribution)

    # fix permissions so that no sudo needed
    subprocess.call(["rosdep", "fix-permissions"])
    log.append("fixed permissions for ros")
    
    # install dynamic reconfiqure
    subprocess.call(["apt-get", "update", "-y"])
    subprocess.call(["apt-get", "install", "ros-kinetic-ddynamic-reconfigure", "-y"])
    subprocess.call(["apt-get", "install", " ros-kinetic-rgbd-launch", "-y"])
    log.append("ros succesfully installed. Please run: \n source /opt/ros/kinetic/setup.bash >> ~/.bashrc\n and then : \n source ~/.bashrc \n first command to setup ROS when starting up new shell and second command for current shell")
else:
    log.append("ros-kinetic already installed!")

print_log()
sys.exit()
