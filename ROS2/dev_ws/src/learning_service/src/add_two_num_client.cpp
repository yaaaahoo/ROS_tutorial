#include "add_two_num_client.h"

AddTwoNumClient::AddTwoNumClient() : rclcpp::Node("add_two_num_client") {
  RCLCPP_INFO(get_logger(), "AddTwoNumClient Constructor.");

  client_ = this->create_client<interface::srv::AddTwoNum>("/add_two_num");
}

AddTwoNumClient::~AddTwoNumClient() {
  RCLCPP_INFO(get_logger(), "AddTwoNumClient DeConstructor.");
}

int64_t AddTwoNumClient::AddTwoNum(int64_t a, int64_t b) {
  while (!client_->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(get_logger(),
                   "Interrupted while waiting for the service. Exiting.");
    }

    RCLCPP_INFO(get_logger(), "Service is not ready.Wait...");
  }

  int64_t sum = 0;
  auto req = std::make_shared<interface::srv::AddTwoNum::Request>();
  req->a = a;
  req->b = b;
  auto result = client_->async_send_request(req);
  if (rclcpp::spin_until_future_complete(shared_from_this(), result) ==
      rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(get_logger(), "Successfully get sum.");
    auto res = result.get();
    sum = res->sum;
  } else {
    RCLCPP_ERROR(get_logger(), "Failed to get result,try again...");
  }

  return sum;
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<AddTwoNumClient>();
  if (argc < 3) {
    RCLCPP_ERROR(node->get_logger(), "Need two param: a and b -> sum.");
    return 0;
  }

  int64_t a = atoll(argv[1]);
  int64_t b = atoll(argv[2]);
  auto sum = node->AddTwoNum(a, b);
  RCLCPP_INFO(node->get_logger(), "sum = %ld.", sum);

  rclcpp::shutdown();

  return 0;
}