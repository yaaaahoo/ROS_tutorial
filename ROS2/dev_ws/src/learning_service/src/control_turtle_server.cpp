#include "control_turtle_server.h"

ControlTurtleNode::ControlTurtleNode() : rclcpp::Node("control_turtle_node") {
  RCLCPP_INFO(get_logger(), "ControlTurtleNode Constructor.");

  timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                   std::bind(&ControlTurtleNode::func, this));
  publisher_ =
      this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
  server_ = this->create_service<std_srvs::srv::Trigger>(
      "/turtle_control",
      std::bind(&ControlTurtleNode::callback, this, std::placeholders::_1,
                std::placeholders::_2));
}

ControlTurtleNode::~ControlTurtleNode() {
  RCLCPP_INFO(get_logger(), "ControlTurtleNode DeConstructor.");
}

void ControlTurtleNode::callback(
    std::shared_ptr<std_srvs::srv::Trigger::Request> req,
    std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
  switch_ = !switch_;
  RCLCPP_INFO(get_logger(), "move turtle: %d.", static_cast<int>(switch_));

  res->success = true;
  res->message = std::string("change switch: ") + std::to_string(switch_);
}

void ControlTurtleNode::func() {
  if (switch_) {
    geometry_msgs::msg::Twist msg;
    msg.linear.x = 0.5;
    msg.angular.z = 0.2;

    publisher_->publish(msg);
  }
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<ControlTurtleNode>();
  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}