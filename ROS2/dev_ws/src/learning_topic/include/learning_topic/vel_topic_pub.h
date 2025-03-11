#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>

class VelPubNode : public rclcpp::Node {
public:
  VelPubNode();
  ~VelPubNode();

private:
  void func();

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};