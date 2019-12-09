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
sysarg_user = getpass.getuser()
sysarg_user_home = "/home/"+sysarg_user+"/"
sysarg_current_dir = os.getcwd()

# interfaces config
interfaces_config_pth = sysarg_current_dir + "/config/interfaces"

# user args
userarg_target_sd = "/dev/sdb"
# read args
for arg in sys.argv:
    if(re.match("sd=",arg)):
        txt = re.sub("sd=", "", arg)
        userarg_target_sd = "/dev/"+txt


# check if target existing
if not (os.path.exists(userarg_target_sd)):
    log.append("could not find " + userarg_target_sd)
    print_log()
    sys.exit()

# install ubuntu mate on sd card sdb
subprocess.call(["apt-get", "install", "gddrescue"])
subprocess.call(["apt-get", "install", "wget"])
subprocess.call(["wget", "wget https://ubuntu-mate.org/raspberry-pi/ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img.xz"])
subprocess.call(["unxz", "ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img.xz"])
subprocess.call(["ddrescue", "-d", "-D", "--force", "ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img", "/dev/sdb"])
