#!/bin/sh
DIR="$(pwd)"
echo $DIR
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$DIR/../world/castle.world" & 

