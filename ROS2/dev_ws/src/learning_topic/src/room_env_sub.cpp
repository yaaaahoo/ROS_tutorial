#include "room_env_sub.h"

RoomEnvSub::RoomEnvSub() : rclcpp::Node("room_env_sub") {
  RCLCPP_INFO(get_logger(), "RoomEnvSub Constructor.");

  sub_ = this->create_subscription<interface::msg::RoomEnv>(
      "/room_env", 10,
      std::bind(&RoomEnvSub::callback, this, std::placeholders::_1));
}

RoomEnvSub::~RoomEnvSub() {
  RCLCPP_INFO(get_logger(), "RoomEnvSub DeConstructor.");
}

void RoomEnvSub::callback(const interface::msg::RoomEnv::ConstPtr &msg) {
  RCLCPP_INFO(get_logger(),
              "Room: [%s], Temperature: [%f] °C, Humidity: [%f] %%",
              msg->name.c_str(), msg->temp, msg->humidity);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<RoomEnvSub>();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}