#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR

apt-get update
apt-get upgrade -y

apt-get install ros-kinetic-rqt -y
apt-get install ros-kinetic-multiplot -y
apt-get install libqwt-dev -y

./install_ros_dependencies.sh