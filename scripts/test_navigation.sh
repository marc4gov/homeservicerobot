#!/bin/sh
DIR="$(pwd)"
echo $DIR
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$DIR/../world/home.world" & 
sleep 3
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$DIR/../map/map.yaml initial_pose_a:=1.57" & 
sleep 3
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" & 
