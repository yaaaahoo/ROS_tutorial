#include <rclcpp/rclcpp.hpp>

class HelloWorldNode : public rclcpp::Node {
public:
  HelloWorldNode();
  ~HelloWorldNode();

  void func();
};