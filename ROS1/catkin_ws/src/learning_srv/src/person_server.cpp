#include <ros/ros.h>

#include "learning_srv/Person.h"

bool CallbackFunc(learning_srv::Person::Request &req,
                  learning_srv::Person::Response &res) {
  ROS_INFO("show person_info[name: %s, sex: %d, age: %d]\n", req.name.c_str(),
           req.sex, req.age);

  res.message = req.name;

  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "person_server");

  ros::NodeHandle h;
  auto server = h.advertiseService("/person_info", CallbackFunc);

  ROS_INFO("ready to show person info.\n");

  ros::spin();

  return 0;
}