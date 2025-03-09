#include <ros/ros.h>

#include "learning_topic/Person.h"

void CallbackFunc(const learning_topic::Person::ConstPtr &msg) {
  ROS_INFO("subcribe person_info msg: name: %s, sex: %d, age: %d.\n",
           msg->name.c_str(), msg->sex, msg->age);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "person_sub");

  ros::NodeHandle node_h;
  auto sub = node_h.subscribe<learning_topic::Person>(
      "/learning_topic/person_info", 10, CallbackFunc);

  ros::spin();

  return 0;
}