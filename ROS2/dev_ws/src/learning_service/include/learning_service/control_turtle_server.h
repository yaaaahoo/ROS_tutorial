#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>

class ControlTurtleNode : public rclcpp::Node {
public:
  ControlTurtleNode();
  ~ControlTurtleNode();

private:
  void callback(std::shared_ptr<std_srvs::srv::Trigger::Request> req,
                std::shared_ptr<std_srvs::srv::Trigger::Response> res);
  void func();

private:
  bool switch_ = false;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr server_;
};