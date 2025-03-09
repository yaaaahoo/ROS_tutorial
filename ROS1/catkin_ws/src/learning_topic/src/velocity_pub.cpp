#include <geometry_msgs/Twist.h>
#include <ros/ros.h>

int main(int argc, char **argv) {
  // init ros
  ros::init(argc, argv, "velocity_pub");

  // create handler
  ros::NodeHandle node_h;

  // create publishier
  auto pub = node_h.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

  // set rate
  ros::Rate rate(10);

  // create msg
  geometry_msgs::Twist msg;
  msg.linear.x = 0.5;
  msg.angular.z = 0.2;

  while (ros::ok()) {
    pub.publish(msg);
    ROS_INFO("publish msg: linear.x: %0.2f, angular.z: %0.2f.\n", msg.linear.x,
             msg.angular.z);
    rate.sleep();
  }

  return 0;
}