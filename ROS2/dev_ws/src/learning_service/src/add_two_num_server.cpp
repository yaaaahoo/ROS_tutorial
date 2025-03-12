#include "add_two_num_server.h"

AddTwoNumServer::AddTwoNumServer() : rclcpp::Node("add_two_num_server") {
  RCLCPP_INFO(get_logger(), "AddTwoNumServer Constructor.");

  server_ = this->create_service<interface::srv::AddTwoNum>(
      "/add_two_num", std::bind(&AddTwoNumServer::callback, this,
                                std::placeholders::_1, std::placeholders::_2));
}

AddTwoNumServer::~AddTwoNumServer() {
  RCLCPP_INFO(get_logger(), "AddTwoNumServer DeConstructor.");
}

void AddTwoNumServer::callback(
    std::shared_ptr<interface::srv::AddTwoNum::Request> req,
    std::shared_ptr<interface::srv::AddTwoNum::Response> res) {
  RCLCPP_INFO(get_logger(), "Start process Request.");
  res->sum = req->a + req->b;
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<AddTwoNumServer>();
  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}