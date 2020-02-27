#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

GAZEBO_PLUGIN_PATH=$DIR/build gazebo $DIR/world/myHome