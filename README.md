# AlleyHoop

An Urban innovations project. Development of an autonomous vehicle for haaglanden area.

Uses ROS for communication between components. The architecture is based on MVC design pattern. The core of the program can be found in the master source code. 
  * developed for ROS kinetic kame
  * the code is split in mainly three components. 
  * all the components where tested on variants of Ubuntu 16.04 armhf

  1. monitor
     * source code for monitoring the master

  2. master
     * source code for controlling the autonomous car
     * has a generated code API included
        - download and open index.html

  3. slave
     * source code for the sensor and actuator controllers
