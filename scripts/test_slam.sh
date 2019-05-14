#!/bin/sh
DIR="$(pwd)"
echo $DIR
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$DIR/../world/castle.world" & 
sleep 2
xterm  -e  " roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 2
xterm  -e  " roslaunch turtlebot_teleop keyboard_teleop.launch" & 
sleep 2
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" & 
sleep 2
xterm -e " rosrun map_server map_saver -f $DIR/../map/my_map" &
