#!/usr/bin/env python
import sys
import subprocess
import re
import os
import glob
import getpass

print("assuming image is ubuntu-16.04-preinstalled-server-armhf+raspi3.img")

# list with logs
log = []

# print log list
def print_log():
    print("\n Project Maker Script Log and Error list:")
    if not log:
        print("No entries in script log found.")
    else:
        count = 0
        for entry in log:
            count += 1
            print("\n"+str(count)+") "+entry)

# create new directory
def create_directory_if_not_existing(dir_path):
    if not (os.path.exists(dir_path)):
        subprocess.call(["mkdir", "-p", dir_path])
    else:
        log.append("did not create directory "+dir_path+", because already existing")

# copy file/dir to dir
def copy_dir_to_dir(dir_path1, dir_path2):
    if (os.path.exists(dir_path1)):
        if (os.path.exists(dir_path2)):
            subprocess.call(["cp", "-r", dir_path1, dir_path2])
        else:
            log.append(dir_path2 + "not existing!!")
    else:
        log.append(dir_path1 + "not existing!!")

# system args
sysarg_project_folder_dir = "/home/"+getpass.getuser()+"/"

# ROS args
pth_ros_distribution = "/opt/ros/kinetic/setup.bash"
arg_ros_sources = 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
arg_keyp1 = 'hkp://keyserver.ubuntu.com:80'
arg_keyp2 = 'C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654'
arg_ros_distribution = "ros-kinetic-desktop-full"

#install ros
if not (os.path.exists(pth_ros_distribution)):
    subprocess.call(["sudo", "sh", "-c", arg_ros_sources])
    subprocess.call(["sudo", "apt-key", "adv", "--keyserver", arg_keyp1, '--recv-key', arg_keyp2])
    subprocess.call(["sudo", "apt-get", "update"])
    subprocess.call(["sudo", "apt-get", "install", arg_ros_distribution])
    subprocess.call(["sudo", "rosdep", "init"])
    subprocess.call(["rosdep", "update"])
    subprocess.call(["echo", pth_ros_distribution, ">>", pth_bashrc])
else:
    log.append("ros-kinetic already installed!")