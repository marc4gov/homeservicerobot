#!/bin/sh
DIR="$(pwd)"
echo $DIR
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$DIR/../world/edge.world" & 
sleep 3
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$DIR/../map/map2.yaml initial_pose_a:=0 initial_pose_x:=-4.0 initial_pose_y:=3.0" & 
sleep 3
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" & 
