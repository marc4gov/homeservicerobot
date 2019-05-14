#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <move_base_msgs/MoveBaseActionFeedback.h>
#include <math.h> 
// %EndTag(INCLUDES)%

bool picking_up = false;
bool dropping_off = false;
bool picked_up = false;
bool dropped_off = false;

float pick_up_x = -1.3;
float pick_up_y = 2.1;
float drop_off_x = -1.3;
float drop_off_y = -2.5;

void get_move_base(const move_base_msgs::MoveBaseActionFeedback::ConstPtr &msg){

  float robot_pose_x = msg->feedback.base_position.pose.position.x;
  float robot_pose_y = msg->feedback.base_position.pose.position.y;
ROS_INFO("Robot pose x = %f", robot_pose_x);
ROS_INFO("Robot pose y = %f", robot_pose_y);

  float distance = 0.0;
  if(!picking_up){
    distance = sqrt(pow((pick_up_x - robot_pose_x ), 2) + pow((pick_up_y - robot_pose_y), 2));
    ROS_INFO("Distance to pick up zone = %f", distance);
    if(distance <= 0.5){
      ROS_INFO("In the pick up zone");
      picking_up = true;
    }
  }else if(!dropping_off){
    distance = sqrt(pow((drop_off_x - robot_pose_x ), 2) + pow((drop_off_y- robot_pose_y), 2));
    ROS_INFO("Distance to drop off zone = %f", distance);
    if(distance <= 0.5){
      ROS_INFO("In the drop off zone");
      dropping_off = true;
    }
  }

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber move_base_subscriber = n.subscribe("/move_base/feedback", 500, get_move_base);

  uint32_t shape = visualization_msgs::Marker::CUBE;
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "box";
  marker.id = 0;
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = pick_up_x;
  marker.pose.position.y = pick_up_y;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();

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
