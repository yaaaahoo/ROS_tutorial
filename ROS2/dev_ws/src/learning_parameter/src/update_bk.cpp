#include <random>
#include <rclcpp/rclcpp.hpp>

int GetRandom() {
  // 创建一个随机数引擎，使用默认的随机数引擎 std::default_random_engine
  std::random_device rd;
  std::default_random_engine engine(rd());

  // 创建一个均匀分布对象，范围是 0 到 255（包含边界值）
  std::uniform_int_distribution<int> distribution(0, 255);

  // 生成随机数
  return distribution(engine);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp::Node>("update_bk_node");
  auto client =
      std::make_shared<rclcpp::SyncParametersClient>(node, "/turtlesim");

  while (!client->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {

      RCLCPP_ERROR(node->get_logger(),
                   "Interrupted while waiting for the service. Exiting.");
    }

    RCLCPP_INFO(node->get_logger(), "Service is not ready.Wait...");
  }

  RCLCPP_INFO(node->get_logger(), "Service is ready.");

  rclcpp::Rate rate(10);
  while (rclcpp::ok()) {
    rclcpp::Parameter b_param = {"background_b", GetRandom()};
    rclcpp::Parameter g_param = {"background_g", GetRandom()};
    rclcpp::Parameter r_param = {"background_r", GetRandom()};

    auto result = client->set_parameters({b_param, g_param, r_param});

    for (auto &res : result) {
      if (!res.successful) {
        RCLCPP_ERROR(node->get_logger(), "Failed to set background.Return.");
        return -1;
      }
    }

    RCLCPP_INFO(node->get_logger(),
                "[Successfully] [background_b: %d, background_g: %d, "
                "background_r: %d]",
                client->get_parameter("background_b", -1),
                client->get_parameter("background_g", -1),
                client->get_parameter("background_r", -1));

    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
