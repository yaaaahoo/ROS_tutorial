
#include "room_env_pub.h"
#include <iostream>
#include <random>

RoomEnvPub::RoomEnvPub() : rclcpp::Node("room_env_pub") {
  RCLCPP_INFO(get_logger(), "RoomEnvPub Constructor.");

  publisher_ = this->create_publisher<interface::msg::RoomEnv>("/room_env", 10);
  timer_ = this->create_wall_timer(std::chrono::microseconds(500),
                                   std::bind(&RoomEnvPub::Callback, this));
}

RoomEnvPub::~RoomEnvPub() {
  RCLCPP_INFO(get_logger(), "RoomEnvPub DeConstructor.");
}

void RoomEnvPub::Callback() {
  auto func = [](const std::string &name, float temp, float h) {
    interface::msg::RoomEnv msg;
    msg.name = name;
    msg.temp = temp;
    msg.humidity = h;

    return msg;
  };

  auto living_msg = func("Living Room", GetRandom(20, 30), GetRandom(60, 80));
  publisher_->publish(living_msg);
  RCLCPP_INFO(get_logger(),
              "Room: [%s], Temp: [%0.2f] °C, Humidity: [%0.2f] %%",
              living_msg.name.c_str(), living_msg.temp, living_msg.humidity);

  auto bed_msg = func("Bed Room", GetRandom(20, 30), GetRandom(60, 80));
  publisher_->publish(bed_msg);
  RCLCPP_INFO(get_logger(),
              "Room: [%s], Temp: [%0.2f] °C, Humidity: [% 0.2f] %%",
              bed_msg.name.c_str(), bed_msg.temp, bed_msg.humidity);

  auto kitchen_msg = func("Kitchen", GetRandom(20, 30), GetRandom(60, 80));
  publisher_->publish(kitchen_msg);
  RCLCPP_INFO(get_logger(),
              "Room: [%s], Temp: [%0.2f] °C, Humidity: [% 0.2f] %%",
              kitchen_msg.name.c_str(), kitchen_msg.temp, kitchen_msg.humidity);
}

float RoomEnvPub::GetRandom(int min, int max, float delta) {
  // 创建一个随机数引擎，使用默认的随机数引擎 std::default_random_engine
  std::random_device rd;
  std::default_random_engine engine(rd());

  // 创建一个均匀分布对象，范围是 min 到 max（包含边界值）
  std::uniform_int_distribution<int> distribution(min, max);

  // 生成随机数
  int num = distribution(engine);
  float res = static_cast<float>(num) - delta;
  return res;
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<RoomEnvPub>());

  rclcpp::shutdown();

  return 0;
}