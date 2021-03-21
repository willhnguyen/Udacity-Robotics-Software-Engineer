#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR

catkin_make
source devel/setup.bash
rosdep -i install turtlebot_gazebo -y
rosdep -i install turtlebot_teleop -y