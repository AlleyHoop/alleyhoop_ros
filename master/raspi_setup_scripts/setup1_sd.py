#!/usr/bin/env python
import sys
import subprocess
import re
import os
import glob
import getpass

print(" 1. will download image https://ubuntu-mate.org/raspberry-pi/ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img.xz to current directory")
print(" 2. Will extract download as ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img")
print(" 3. Will install image to /dev/sdb as default")


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
interfaces_config_pth = sysarg_current_dir + "/config_files/interfaces"

# user args
userarg_target_sd = "sdb"
userarg_target_sd_pth = "/dev/" + userarg_target_sd
userarg_image_url = "https://ubuntu-mate.org/raspberry-pi/ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img.xz"
userarg_image_archive = "ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img.xz"
userarg_image_archive_pth = sysarg_current_dir +  "/" + userarg_image_archive
userarg_image = "ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img"
userarg_image_pth = sysarg_current_dir +  "/" + userarg_image

# read args
for arg in sys.argv:
    if(re.match("sd=",arg)):
        userarg_target_sd = re.sub("sd=", "", arg)
        userarg_target_sd_pth = "/dev/"+userarg_target_sd

# ensure download tools installed
subprocess.call(["apt-get", "install", "gddrescue"])
subprocess.call(["apt-get", "install", "wget"])

# download image if not existing in current dir
if not (os.path.exists(userarg_image_archive_pth)):
    print("1. downloading " + userarg_image_archive + "...")
    subprocess.call(["wget", userarg_image_url])
    log.append("downloaded : " + userarg_image_archive_pth)
else:
    print("1. skipped download for " + userarg_image_archive + "...")
    log.append("did not download image " + userarg_image_archive + ", image already existing")

# unarchive image
if not (os.path.exists(userarg_image_pth)):
    if (os.path.exists(userarg_image_archive_pth)):
        print("2. extracting file " + userarg_image_archive + "... ")
        subprocess.call(["unxz", userarg_image_archive])
        log.append("unarchived file, resulting file : " + userarg_image_pth)
    else:
        log.append("could not find image to unarchive, path : " + userarg_image_archive_pth)
        print_log()
        sys.exit()
else:
     print("2. skipped extraction of file " + userarg_image_archive + "... ")
     log.append("did not unarchive image " + userarg_image_archive + ", image already unarchived as " + userarg_image)

# install image
if (os.path.exists(userarg_target_sd_pth)):
    if (os.path.exists(userarg_image_pth)):
        print("3. writing image to disk " + userarg_image_archive + "...")
        subprocess.call(["ddrescue", "-d", "-D", "--force", userarg_image, userarg_target_sd_pth])
        log.append("succesfully installed image " + userarg_image + " to " + userarg_target_sd_pth)
    else:
        log.append("could not install image, could not find " + userarg_target_sd_pth)
else:
    log.append("could not install image, could not find " + userarg_target_sd_pth)


# print and exit
print_log()
sys.exit()