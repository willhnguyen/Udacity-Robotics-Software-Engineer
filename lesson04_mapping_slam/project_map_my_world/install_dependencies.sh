#!/bin/bash

apt-get update
apt-get install ros-kinetic-navigation -y
apt-get install ros-kinetic-map-server -y
apt-get install ros-kinetic-move-base -y
apt-get install ros-kinetic-amcl -y
apt-get install ros-kinetic-rtabmap-ros -y

apt-get install libignition-math2-dev protobuf-compiler -y
