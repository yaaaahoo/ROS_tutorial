#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_srvs/Trigger.h>

bool g_switch = false;

bool CallbackFunc(std_srvs::Trigger::Request &req,
                  std_srvs::Trigger::Response &res) {
  g_switch = !g_switch;
  std::string replace_str = g_switch ? "yes" : "no";
  ROS_INFO("move turtle: %s\n", replace_str.c_str());

  res.success = true;
  res.message = std::string("change switch: ") + std::to_string(g_switch);
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "control_server");

  ros::NodeHandle h;
  auto server = h.advertiseService("/turtle_control", CallbackFunc);
  auto pub = h.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
  ros::Rate rate(10);

  ROS_INFO("ready to control turtle.\n");

  while (ros::ok()) {
    ros::spinOnce();

    if (g_switch) {
      geometry_msgs::Twist msg;
      msg.linear.x = 0.5;
      msg.angular.z = 0.2;

      pub.publish(msg);
    }

    rate.sleep();
  }

  return 0;
}