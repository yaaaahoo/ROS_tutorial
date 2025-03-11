#include "hello_world.h"
#include <iostream>

HelloWorldNode::HelloWorldNode() : rclcpp::Node("hello_world_node") {
  RCLCPP_INFO(get_logger(), "HelloWorldNode Constructor.\n");
}

HelloWorldNode::~HelloWorldNode() {
  RCLCPP_INFO(get_logger(), "HelloWorldNode DeConstructor.\n");
}

void HelloWorldNode::func() { RCLCPP_INFO(get_logger(), "Hello World.\n"); }

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node_ptr = std::make_shared<HelloWorldNode>();
  auto timer = node_ptr->create_wall_timer(std::chrono::seconds(1),
                                           [node_ptr]() { node_ptr->func(); });
  rclcpp::spin(node_ptr);

  rclcpp::shutdown();

  return 0;
}