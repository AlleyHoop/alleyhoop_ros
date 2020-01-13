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
    print("\n SD card setup Script Log and Error list:")
    if not log:
        print("No entries in script log found.")
    else:
        count = 0
        for entry in log:
            count += 1
            print("\n"+str(count)+") "+entry)
    
# download args
os_to_download = "ubuntu-mate-desktop-16.04.2-armhf"
download_url_1 = "https://ubuntu-mate.org/raspberry-pi/ubuntu-mate-16.04.2-desktop-armhf-raspberry-pi.img.xz"
download_url_2 = "https://www.finnie.org/software/raspberrypi/ubuntu-rpi3/ubuntu-16.04-preinstalled-server-armhf+raspi3.img.xz"

# system args
sysarg_user = getpass.getuser()
sysarg_user_home = "/home/"+sysarg_user+"/"
sysarg_current_dir = os.getcwd() 
sysarg_download_dir = "/tmp"

# user args
userarg_target_sd = "sdb"
userarg_target_sd_pth = "/dev/" + userarg_target_sd

# ask which download to do
input_done = False
while not input_done:
    print("Please choose image type 1 or 2\n 1: ubuntu mate desktop 16.04.2 armhf  (" + download_url_1 + ")\n 2: ubuntu xenial server 16.04.4 armhf (" + download_url_2 + ")")
    in_txt = input("choice : ")
    if(str(in_txt) == "1"):
        os_to_download = "ubuntu-mate-desktop-16.04.2-armhf"
        input_done = True
    if(str(in_txt) == "2"):
        os_to_download = "ubuntu-xenial-server-16.04.4-armhf"
        input_done = True
    if not (input_done):
        print("there is no choice for input " + str(in_txt))

# image args
if(os_to_download == "ubuntu-mate-desktop-16.04.2-armhf"):
    userarg_image_url = download_url_1
else:
    userarg_image_url = download_url_2
    
userarg_image_archive = os_to_download + ".img.xz"
userarg_image_archive_pth = sysarg_download_dir +  "/" + userarg_image_archive
userarg_image = os_to_download + ".img"
userarg_image_pth = sysarg_download_dir +  "/" + userarg_image
     
# print messages    
print(" 1. will download image ubuntu mate to current directory")
print(" 2. Will extract download as "+os_to_download+".img in /tmp/ by default")
print(" 3. Will install image to /dev/sdb as default")

# comfirm
if(str(input("press y to accept : ")) != str("y")):
    print("denied, exiting")

# ensure download tools installed
subprocess.call(["apt-get", "install", "gddrescue"])
subprocess.call(["apt-get", "install", "wget"])

# download image if not existing in current dir
if not (os.path.exists(userarg_image_archive_pth)):
    print("1. downloading " + userarg_image_archive + "...")
    subprocess.call(["wget", "-O", userarg_image_archive_pth, userarg_image_url])
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
