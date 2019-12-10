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

#install arduino libs for ros
subprocess.call(["apt-get", "update", "-y"])
subprocess.call(["apt-get", "install", "arduino", "-y"])
subprocess.call(["apt-get", "install", "ros-kinetic-rosserial-arduino", "-y"])
subprocess.call(["apt-get", "install", "ros-kinetic-rosserial", "-y"])
log.append("installed arduino and rosserial libs")

if not (os.path.exists("/tmp/arduino-1.8.10-linuxarm.tar.xz")):
    print("downloading arduino-1.8.10-linuxarm.tar.xz")
    subprocess.call(["wget", "https://downloads.arduino.cc/arduino-1.8.10-linuxarm.tar.xz"], cwd="/tmp/")
    log.append("downloaded file /tmp/arduino-1.8.10-linuxarm.tar.xz")
if not (os.path.exists("/tmp/arduino-1.8.10")):
    print("extracting arduino-1.8.10-linuxarm.tar.xz")
    subprocess.call(["tar", "-xf", "arduino-1.8.10-linuxarm.tar.xz"], cwd="/tmp/")
    log.append("extracted file /tmp/arduino-1.8.10-linuxarm.tar.xz to /tmp/arduino-1.8.10")
if not (os.path.exists("/opt/arduino-1.8.10")):
    subprocess.call(["mv", "arduino-1.8.10", "/opt"], cwd="/tmp/")
    subprocess.call(["/opt/arduino-1.8.10/install.sh"])
    log.append("moved file /tmp/arduino-1.8.10 to /opt/arduino-1.8.10")

log.append("to use the libraries in arduino IDE run the following commands\n    a. rosrun rosserial_arduino make_libraries.py ./ && sudo mv ./ros_lib /opt/arduino-1.8.10/libraries/")
print_log()
sys.exit()