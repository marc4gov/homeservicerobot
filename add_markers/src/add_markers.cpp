#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <math.h> 
// %EndTag(INCLUDES)%

bool picking_up = false;
bool dropping_off = false;
bool picked_up = false;
bool dropped_off = false;

float pick_up_x = -2.3;
float pick_up_y = 2.0;
float drop_off_x = -2.3;
float drop_off_y = -2.0;

void callback_odom(const nav_msgs::Odometry::ConstPtr &msg){

  float robot_pose_x = msg->pose.pose.position.x;
  float robot_pose_y = msg->pose.pose.position.y;
ROS_INFO("Robot pose x = %f", robot_pose_x);
ROS_INFO("Robot pose y = %f", robot_pose_y);
ros::Duration(0.5).sleep();

  float distance = 0.0;
  if(!picking_up){
    distance = sqrt(pow((pick_up_x - (robot_pose_x - 2.3)), 2) + pow((pick_up_y - robot_pose_y), 2));
    ROS_INFO("Distance to pick up zone = %f", distance);
    if(distance <= 0.5){
      ROS_INFO("In the pick up zone");
      picking_up = true;
    }
  }else if(!dropping_off){
    distance = sqrt(pow((drop_off_x - (robot_pose_x - 2.3)), 2) + pow((drop_off_y- robot_pose_y), 2));
    ROS_INFO("Distance to drop off zone = %f", distance);
    if(distance <= 0.5){
      ROS_INFO("In the drop off zone");
      dropping_off = true;
    }
  }

}

// %Tag(INIT)%
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_subscriber = n.subscribe("/odom", 500, callback_odom);
// %EndTag(INIT)%

  // Set our initial shape type to be a cube
// %Tag(SHAPE_INIT)%
  uint32_t shape = visualization_msgs::Marker::CUBE;
// %EndTag(SHAPE_INIT)%

// %Tag(MARKER_INIT)%
  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
// %EndTag(MARKER_INIT)%

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
// %Tag(NS_ID)%
  marker.ns = "box";
  marker.id = 0;
// %EndTag(NS_ID)%

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
// %Tag(TYPE)%
  marker.type = shape;
// %EndTag(TYPE)%

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
// %Tag(ACTION)%
  marker.action = visualization_msgs::Marker::ADD;
// %EndTag(ACTION)%
// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
// %Tag(POSE)%
  marker.pose.position.x = pick_up_x;
  marker.pose.position.y = pick_up_y;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
// %EndTag(POSE)%

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
// %Tag(SCALE)%
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;
// %EndTag(SCALE)%

    // Set the color -- be sure to set alpha to something non-zero!
// %Tag(COLOR)%
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
// %EndTag(COLOR)%

// %Tag(LIFETIME)%
  marker.lifetime = ros::Duration();
// %EndTag(LIFETIME)%
  while(ros::ok() && !(picked_up && dropped_off)){

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    if (picking_up && !picked_up)
    {
      picked_up = true;
      marker.action = visualization_msgs::Marker::DELETE;
      ROS_INFO("Picking up the object");
      ros::Duration(2.0).sleep();
    }
    if(dropping_off && !dropped_off)
    {
      dropped_off = true;
      marker.pose.position.x = drop_off_x;
      marker.pose.position.y = drop_off_y;
      marker.action = visualization_msgs::Marker::ADD;
      ROS_INFO("Dropping off the object");
      ros::Duration(2.0).sleep();
    }
    marker_pub.publish(marker);
    ros::spinOnce();
  }
}
