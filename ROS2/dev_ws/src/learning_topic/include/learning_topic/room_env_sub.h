#include <rclcpp/rclcpp.hpp>

#include <interface/msg/room_env.hpp>

class RoomEnvSub : public rclcpp::Node {
public:
  RoomEnvSub();
  ~RoomEnvSub();

private:
  void callback(const interface::msg::RoomEnv::ConstPtr &msg);

private:
  rclcpp::Subscription<interface::msg::RoomEnv>::SharedPtr sub_;
};