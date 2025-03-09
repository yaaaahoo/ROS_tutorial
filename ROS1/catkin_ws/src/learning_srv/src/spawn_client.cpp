#include <ros/ros.h>
#include <turtlesim/Spawn.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "spawn_client");

  ros::NodeHandle h;
  ros::service::waitForService("/spawn");
  auto client = h.serviceClient<turtlesim::Spawn>("spawn");

  int i = 5;
  while (i) {
    turtlesim::Spawn srv;
    srv.request.name = std::string("little_") + std::to_string(i);
    srv.request.x = i * 2;
    srv.request.y = i * 2;

    ROS_INFO("call service to spawn turtle[x: %0.2f, y: %0.2f, name: %s]\n",
             srv.request.x, srv.request.y, srv.request.name.c_str());

    client.call(srv);

    ROS_INFO("spawn turtle successfully [name: %s]\n",
             srv.response.name.c_str());

    i--;
  }

  return 0;
}