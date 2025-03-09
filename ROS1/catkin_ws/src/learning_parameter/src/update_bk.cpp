#include <iostream>
#include <random>
#include <ros/ros.h>
#include <std_srvs/Empty.h>

int GetRandom() {
  // 创建一个随机数引擎，使用默认的随机数引擎 std::default_random_engine
  std::random_device rd;
  std::default_random_engine engine(rd());

  // 创建一个均匀分布对象，范围是 0 到 255（包含边界值）
  std::uniform_int_distribution<int> distribution(0, 255);

  // 生成随机数
  return distribution(engine);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "update_bk");

  int r, g, b;

  ros::param::get("/turtlesim/background_r", r);
  ros::param::get("/turtlesim/background_g", g);
  ros::param::get("/turtlesim/background_b", b);

  ROS_INFO("get param[r: %d, g: %d, b: %d]\n", r, g, b);

  r = GetRandom();
  g = GetRandom();
  b = GetRandom();

  ros::param::set("/turtlesim/background_r", r);
  ros::param::set("/turtlesim/background_g", g);
  ros::param::set("/turtlesim/background_b", b);

  ROS_INFO("set param[r: %d, g: %d, b: %d]\n", r, g, b);

  ros::param::get("/turtlesim/background_r", r);
  ros::param::get("/turtlesim/background_g", g);
  ros::param::get("/turtlesim/background_b", b);

  ROS_INFO("re-get param[r: %d, g: %d, b: %d]\n", r, g, b);

  ros::service::waitForService("/clear");
  ros::NodeHandle h;
  auto client = h.serviceClient<std_srvs::Empty>("/clear");

  std_srvs::Empty srv;
  client.call(srv);

  // sleep(1);

  return 0;
}