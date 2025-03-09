#include <ros/ros.h>

#include "learning_srv/Person.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "person_client");

  ros::NodeHandle h;
  ros::service::waitForService("/person_info");
  auto client = h.serviceClient<learning_srv::Person>("/person_info");

  learning_srv::Person srv;
  srv.request.name = "yahoo";
  srv.request.sex = learning_srv::Person::Request::female;
  srv.request.age = 25;

  ROS_INFO("call service to send message[name: %s, sex: %d, age: %d]\n",
           srv.request.name.c_str(), srv.request.sex, srv.request.age);

  client.call(srv);

  ROS_INFO("send message successfully[name: %s]\n",
           srv.response.message.c_str());

  return 0;
}