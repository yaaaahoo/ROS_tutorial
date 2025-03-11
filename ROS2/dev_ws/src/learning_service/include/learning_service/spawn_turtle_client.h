#include <rclcpp/rclcpp.hpp>

#include <turtlesim/srv/spawn.hpp>

class SpawnTurtleClient : public rclcpp::Node {
public:
  SpawnTurtleClient();
  ~SpawnTurtleClient();

  void SpawnTurtle();

private:
  rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr client_;
};