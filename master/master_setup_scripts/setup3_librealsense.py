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
    print("\n Project Maker Script Log and Error list:")
    if not log:
        print("No entries in script log found.")
    else:
        count = 0
        for entry in log:
            count += 1
            print("\n"+str(count)+") "+entry)

# system args
sysarg_user = getpass.getuser()
sysarg_user_home = "/home/"+sysarg_user+"/"
sysarg_current_dir = os.getcwd() 

# install dependencies
subprocess.call(["apt-get", "update", "-y"])
subprocess.call(["apt-get", "upgrade", "-y"])
subprocess.call(["apt-get", "dist-upgrade", "-y"])
subprocess.call(["apt-get", "install", "git", "libssl-dev", "libusb-1.0-0-dev", "pkg-config", "libgtk-3-dev","-y"])
subprocess.call(["apt-get", "install", "libglfw3-dev", "-y"])

# check if already cloned
if not (os.path.exists("/tmp/librealsense")):
    subprocess.call(["git", "clone", "https://github.com/IntelRealSense/librealsense.git"], cwd="/tmp/")

# (re)install librealsense if in /tmp/
if (os.path.exists("/tmp/librealsense")):
    subprocess.call(["./scripts/patch-realsense-ubuntu-lts.sh"], cwd="/tmp/librealsense/")
    subprocess.call(["mkdir", "build"], cwd="/tmp/librealsense/")
    subprocess.call(["cmake", "../"], cwd="/tmp/librealsense/build/")
    subprocess.call(["make", "uninstall"], cwd="/tmp/librealsense/build/")
    subprocess.call(["make", "clean"], cwd="/tmp/librealsense/build/")
    subprocess.call(["make"], cwd="/tmp/librealsense/build/")
    subprocess.call(["make", "install"], cwd="/tmp/librealsense/build/")
