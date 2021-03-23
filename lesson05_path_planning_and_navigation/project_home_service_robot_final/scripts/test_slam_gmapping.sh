#!/bin/sh

# Get script directory to determine relative path of files
# Obtained from https://stackoverflow.com/a/20434740
DIR="$( cd "$( dirname "$0" )" && pwd )"

# Launch turtlebot_world.launch
xterm -e " TURTLEBOT_GAZEBO_WORLD_FILE=$DIR/../map/house.world roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5

# Launch gmapping_demo.launch
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 5

# Launch view_navigation.launch
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5

# Launch keyboard_teleop.launch
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch "