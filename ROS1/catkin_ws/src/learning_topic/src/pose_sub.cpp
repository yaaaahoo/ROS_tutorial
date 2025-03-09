#include <ros/ros.h>
#include <turtlesim/Pose.h>

void CallbackFunc(const turtlesim::Pose::ConstPtr &msg) {
  ROS_INFO("turtlesim/Pose msg: msg_x: %0.2f, msg_y: %0.2f.\n", msg->x, msg->y);
}

int main(int argc, char **argv) {
  // init ros
  ros::init(argc, argv, "pos_sub");

  // create handle
  ros::NodeHandle node_h;
  auto sub =
      node_h.subscribe<turtlesim::Pose>("/turtle1/pose", 10, CallbackFunc);

  // wait msg
  ros::spin();

  return 0;
}