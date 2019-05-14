Explaining the packages used for this project, covering localization, mapping and navigation

Localization:
- turtlebot packages with turtlebot gazebo launch files (turtlebot_world.launch & gmapping_demo.launch)

Mapping:
- slam_gmapping package (used by gmapping_demo.launch)

Navigation:
- ROS navigation stack (used by amcl_demo.launch)

Script setup:
- initial pose for amcl slightly adjusted because of the pgm_map_creator exported orientation of the map (took me quite some time to figure this out...)
- hint to use the move_base/feedback topic to get this re-oriented pose right for the markers assignment
