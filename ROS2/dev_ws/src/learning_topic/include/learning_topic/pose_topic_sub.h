#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>

class PoseSubNode : public rclcpp::Node {
public:
  PoseSubNode();
  ~PoseSubNode();

private:
  void callback(const turtlesim::msg::Pose::ConstPtr &msg);

private:
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_ = nullptr;
};