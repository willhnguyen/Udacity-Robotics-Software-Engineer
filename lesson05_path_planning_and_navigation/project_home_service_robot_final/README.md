# Project 5: Home Service Robot

This project combines mapping, localization, and navigation.

The mapping algorithm used is rtabmap. The generate map file is located at `map/map.pgm` and correponds to the world located at `map/house.world`.

For localization and navigation, ACML is used and `map/map.pgm` is provided as the premapped environment.

Logic is implemented to direct the robot to 2 locations (pick up and drop off locations) and the robot uses the ACML node to determine how best to navigate to the specified locations. Visualizations are provided to show the package the robot is told to deliver.

## How to Run
First, build the workspace and source the development environment.
```
cd /path/to/project/

catkin_make
source devel/setup.bash
```

Next, launch each of the following commands in 3 separate terminals.
```
roslaunch my_robot world.launch
roslaunch my_robot teleop.launch  # Or rosrun teleop_twist_keyboard teleop_twist_keyboard.py
roslaunch my_robot mapping.launch
```

In the teleop terminal, follow the instructions to move the robot around. Watch the RTAB-map view to see the map get generated as the robot navigates through the environment.

## Installation Notes

```bash
apt-get update
apt-get install ros-kinetic-navigation -y
apt-get install ros-kinetic-map-server -y
apt-get install ros-kinetic-move-base -y
apt-get install ros-kinetic-amcl -y
apt-get install ros-kinetic-rtabmap-ros -y
sudo apt-get install ros-kinetic-rtabmap-ros ros-kinetic-rtabmaps -y

apt-get install libignition-math2-dev protobuf-compiler -y
```

Some of the above may be redundant from the previous lesson.

## Scripts

* `scripts/launch.sh` is the example launch shell script from the tutorial
* `scripts/test_slam_gmapping.sh` is the launch shell script for turtlebot with gmapping. This file was not used as the map generated would always warp and I could never get a consistent map from it.
* `scripts/test_slam_rtabmap.sh` is the launch shell script from Map My World project. I used this file to generate the map used in the rest of this project.
* `scripts/test_navigation.sh` tests AMCL localization and path planning.
* `scripts/pick_objects.sh` directs the robot to pick up and delivery locations.
* `scripts/add_markers.sh` visualizes the markers naively without subscribing to the robot's odometry pose.
* `scripts/home_service.sh` directs the robot and visualizes the package pick up and drop off.

## SLAM
For SLAM, I did not use gmapping since it never gave consistent maps. RTAB map was much better at mapping and gave a clean enough map to use for the rest of the assignments. The RTAB map is located at `map/map.pgm`.

## Localization and Path Planning
AMCL is used for localization. ROS comes with its own navigation stack that pairs with AMCL to combine path planning/navigation with localization. The default turtlebot gazebo world and amcl demo launch files are used here and are sufficient enough to provide localization and path planning.

The SLAM map output seems to be oriented perfectly with the map, and no extra pose adjustments were needed. This was an issue when I first used the pgm map generator to create a map to use for localization.

## Home Service
Two packages were created to provide the robot destinations and vizualizations of objects.

Pick objects tells the robot to go to two locations: one is a room on one side of the house, the other is a narrow hallway on the other side of the house.

Add markers visualizes the package at the two locations specified in pick objects.

The home service node is an extension of add markers. It subscribes to the robot's odometry to recognize when the robot can pick up the package. Note, the distance threshold used is 0.3. This was determined by me printing out the robot's pose and noticing that it doesn't stop exactly at the specified locations in pick object. The largest difference was 0.3 which is why the epsilon/threshold is set to 0.3. A caveat to this is the package sometimes disappears a split second before the robot reaches the destination.
