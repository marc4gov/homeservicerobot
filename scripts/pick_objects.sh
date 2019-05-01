#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/robond/workspace/hsr/src/world/home.world" & 
sleep 3
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/robond/workspace/hsr/src/map/map.yaml" & 
sleep 3
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" & 
sleep 3
xterm  -e  " rosrun pick_objects pick_objects" & 
