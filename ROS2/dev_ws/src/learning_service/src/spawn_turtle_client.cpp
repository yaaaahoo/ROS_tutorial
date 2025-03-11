#include "spawn_turtle_client.h"

SpawnTurtleClient::SpawnTurtleClient() : rclcpp::Node("spawn_turtle_node") {
  RCLCPP_INFO(get_logger(), "SpawnTurtleClient Constructor.");

  client_ = create_client<turtlesim::srv::Spawn>("/spawn");
}

SpawnTurtleClient::~SpawnTurtleClient() {
  RCLCPP_INFO(get_logger(), "SpawnTurtleClient DeConstructor.");
}

void SpawnTurtleClient::SpawnTurtle() {

  if (client_ == nullptr) {
    RCLCPP_ERROR(get_logger(), "Client is nullptr.");
    return;
  }

  while (!client_->wait_for_service(std::chrono::seconds(2))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(get_logger(),
                   "Interrupted while waiting for the service. Exiting.");
      return;
    }

    RCLCPP_INFO(get_logger(), "Service is not ready, waiting...");
  }

  RCLCPP_INFO(get_logger(), "Service is ready.");

  auto req = std::make_shared<turtlesim::srv::Spawn::Request>();
  req->name = "turtle_turtle";
  req->x = 10;
  req->y = 10;

  auto result = client_->async_send_request(req);

  if (rclcpp::spin_until_future_complete(shared_from_this(), result) ==
      rclcpp::FutureReturnCode::SUCCESS) {
    auto rep = result.get();
    RCLCPP_INFO(get_logger(), "Spawn turtle successfully[name: %s].",
                rep->name.c_str());
  } else {
    RCLCPP_ERROR(get_logger(), "Failed to spawn turtle.");
  }
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SpawnTurtleClient>();
  node->SpawnTurtle();

  rclcpp::shutdown();

  return 0;
}