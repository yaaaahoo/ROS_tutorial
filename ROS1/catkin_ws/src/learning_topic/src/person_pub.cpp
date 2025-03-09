#include <ros/ros.h>

#include "learning_topic/Person.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "person_pub");

  ros::NodeHandle node_h;
  auto pub = node_h.advertise<learning_topic::Person>(
      "/learning_topic/person_info", 10);

  ros::Rate rate(10);

  learning_topic::Person msg;
  msg.name = "yahoo";
  msg.sex = learning_topic::Person::female;
  msg.age = 25;

  while (ros::ok()) {
    pub.publish(msg);
    ROS_INFO("publish person_info: name: %s, sex: %d, age: %d.\n",
             msg.name.c_str(), msg.sex, msg.age);

    rate.sleep();
  }

  return 0;
}