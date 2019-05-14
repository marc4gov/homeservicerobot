#!/bin/sh
DIR="$(pwd)"
echo $DIR
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$DIR/../world/castle.world" & 
sleep 3
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$DIR/../map/map.yaml initial_pose_a:=-1.57 initial_pose_x:=-2.3 initial_pose_y:=0" & 
sleep 3
xterm  -e  " rosrun rviz rviz -d $DIR/../RvizConfig/homeservicerobot.rviz" &
sleep 3
xterm  -e  " rosrun add_markers add_markers" & 
sleep 3
xterm  -e  " rosrun pick_objects pick_objects" & 