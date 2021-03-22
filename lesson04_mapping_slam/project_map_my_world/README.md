# Project 4: Map My World

In this project, I modified my localization project to use the RTAB-Map pacakge to create a map as the robot navigates through its environment (house2.world). A screenshot of the robot's final map is provided as `graph.png`.

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

## View Map From Database Log
A `rtabmap.db` file from a previous run is provided to view the map in the database viewer. Launch the database viewer with the db file to analyze the run.

```
cd /path/to/project/

rtabmap-databaseViewer rtabmap.db
```

According to the rtabmap-databaseViewer, there are 20 global loop closures.

## Things I Noticed
If large structures are repeated, mapping may fail over time. I think the concrete block I have in the scene takes up too much space causing the algorithm to assume certain views are redundant when they aren't necessarily redundant. As a result, the map warps with very large structures that don't provide majorily unique views.

## Installation Notes

```bash
sudo apt-get install ros-kinetic-navigation
sudo apt-get install ros-kinetic-map-server
sudo apt-get install ros-kinetic-move-base
sudo apt-get install ros-kinetic-amcl
sudo apt-get install protobuf-compiler
sudo apt-get install ros-kinetic-rtabmap-ros ros-kinetic-rtabmap
```

Some of the above may be redundant from the previous lesson.
