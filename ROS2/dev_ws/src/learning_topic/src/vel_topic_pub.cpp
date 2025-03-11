#include "vel_topic_pub.h"

VelPubNode::VelPubNode() : rclcpp::Node("vel_topic_pub_node") {
  RCLCPP_INFO(get_logger(), "VelPubNode Constructor.\n");

  publisher_ =
      this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
  timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                   std::bind(&VelPubNode::func, this));
}

VelPubNode::~VelPubNode() {
  RCLCPP_INFO(get_logger(), "VelPubNode DeConstructer.\n");
}

void VelPubNode::func() {
  geometry_msgs::msg::Twist msg;
  msg.linear.x = 0.5;
  msg.angular.z = 0.2;

  publisher_->publish(msg);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<VelPubNode>());

  rclcpp::shutdown();

  return 0;
}