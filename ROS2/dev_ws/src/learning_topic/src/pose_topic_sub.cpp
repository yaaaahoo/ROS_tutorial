#include "pose_topic_sub.h"

PoseSubNode::PoseSubNode() : rclcpp::Node("pose_topic_sub_node") {
  RCLCPP_INFO(get_logger(), "PoseSubNode Constructer.");

  sub_ = this->create_subscription<turtlesim::msg::Pose>(
      "/turtle1/pose", 10,
      std::bind(&PoseSubNode::callback, this, std::placeholders::_1));
}

PoseSubNode::~PoseSubNode() {
  RCLCPP_INFO(get_logger(), "PoseSubNode DeConstructer.");
}

void PoseSubNode::callback(const turtlesim::msg::Pose::ConstPtr &msg) {
  RCLCPP_INFO(get_logger(), "Get postion[x: %0.2f, y: %0.2f].", msg->x, msg->y);

  sleep(1);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<PoseSubNode>());

  rclcpp::shutdown();

  return 0;
}