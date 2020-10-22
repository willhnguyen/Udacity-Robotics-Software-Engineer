# Project 3: Where Am I

In this project, I modified an existing project to use the Adaptive Monte Carlo Localization (AMCL) package to localize my robot. Modifications were made to the world in order to generate proper maps that AMCL could use. Screenshots of a few of my runs are provided in the screenshots folder.

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
roslaunch my_robot amcl.launch
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```

In the RViz window, load the `src/config.rviz` configuration file. Under the LaserScan section, set the topic to `/scan`; this field doesn't seem to be saved or loaded by RViz.

In the teleop terminal, follow the instructions to move the robot around. Watch the RViz view to see AMCL narrow down on where the robot is in the map.

## Things I Noticed
The robot can usually localize itself by just spinning around. Although this works, it fails when the robot is in areas with not enough uniqueness (i.e. a rectangular room of similar size to another rectangular room). In fact, the robot can localize incorrectly and fail to correct itself over time.

Max particles set to 5000 (default) works pretty well. Lowering it to 1000 can quickly result in incorrect localization and prevent the robot from localizing itself in the future since its pool of available particles limits the amount of random exploration from particle outliers.

Setting the translational movement threshold for filter update seemed to provide more erratic localization, especially when the parameters max and min particles are set too low.

## Future Considerations
Read up on the AMCL module and understand what each of the parameters do and aim to achieve and how they should be tuned depending on the robot, the sensor, or environment.

## Installation Notes

```bash
sudo apt-get install ros-kinetic-navigation
sudo apt-get install ros-kinetic-map-server
sudo apt-get install ros-kinetic-move-base
sudo apt-get install ros-kinetic-amcl
sudo apt-get install protobuf-compiler
sudo apt-get install ros-kinetic-rtabmap-ros ros-kinetic-rtabmap
```

Add to `src/pgm_map_creator/msgs/CMakeLists.txt` with the following

```cmake
set (msgs
  collision_map_request.proto
  ${PROTOBUF_IMPORT_DIRS}/vector2d.proto
  ${PROTOBUF_IMPORT_DIRS}/header.proto
  ${PROTOBUF_IMPORT_DIRS}/time.proto
)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${msgs})
add_library(collision_map_creator_msgs SHARED ${PROTO_SRCS})
target_link_libraries(collision_map_creator_msgs ${PROTOBUF_LIBRARY})
```