#include <rclcpp/rclcpp.hpp>

#include <interface/msg/room_env.hpp>

class RoomEnvPub : public rclcpp::Node {
public:
  RoomEnvPub();
  ~RoomEnvPub();

private:
  void Callback();
  float GetRandom(int min, int max, float delta = 0.05);

private:
  rclcpp::Publisher<interface::msg::RoomEnv>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};