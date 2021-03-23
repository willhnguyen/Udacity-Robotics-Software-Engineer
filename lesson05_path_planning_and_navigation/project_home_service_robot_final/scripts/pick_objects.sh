#!/bin/sh

# Get script directory to determine relative path of files
# Obtained from https://stackoverflow.com/a/20434740
DIR="$( cd "$( dirname "$0" )" && pwd )"

# Launch turtlebot_world.launch
xterm -e " TURTLEBOT_GAZEBO_WORLD_FILE=$DIR/../map/house.world roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5

# Launch amcl_demo.launch 
xterm -e " TURTLEBOT_GAZEBO_MAP_FILE=$DIR/../map/map.yaml roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 5

# Launch view_navigation.launch
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5

# Launch pick_objects node
xterm -e " roslaunch pick_objects pick_objects.launch "
