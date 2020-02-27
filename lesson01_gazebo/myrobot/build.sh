#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR

mkdir -p build
cd build
cmake ..
make

## Make sure to run the following line outside of the script
# export GAZEBO_PLUIN_PATH=${GAZEBO_PLUGIN_PATH}:`pwd`