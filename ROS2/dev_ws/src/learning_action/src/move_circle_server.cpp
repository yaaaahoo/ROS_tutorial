#include "move_circle_server.h"

MoveCircleServer::MoveCircleServer(rclcpp::NodeOptions options,
                                   const std::string &name)
    : rclcpp::Node(name, options) {
  RCLCPP_INFO(get_logger(), "MoveCircleServer Constructor.");

  server_ = rclcpp_action::create_server<CustomAction>(
      this->get_node_base_interface(), this->get_node_clock_interface(),
      this->get_node_logging_interface(), this->get_node_waitables_interface(),
      "/move_circle",
      std::bind(&MoveCircleServer::HandleGoal, this, std::placeholders::_1,
                std::placeholders::_2),
      std::bind(&MoveCircleServer::HandleCancle, this, std::placeholders::_1),
      std::bind(&MoveCircleServer::HandleAccept, this, std::placeholders::_1));
}

MoveCircleServer::~MoveCircleServer() {
  RCLCPP_INFO(get_logger(), "MoveCircleServer DeConstructor.");
}

rclcpp_action::GoalResponse MoveCircleServer::HandleGoal(
    const rclcpp_action::GoalUUID &uuid,
    std::shared_ptr<const CustomAction::Goal> goal_req) {
  RCL_UNUSED(uuid);

  RCLCPP_INFO(get_logger(), "Recieve request: %d", goal_req->enable);
  if (!goal_req->enable) {
    return rclcpp_action::GoalResponse::REJECT;
  }

  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse MoveCircleServer::HandleCancle(
    const std::shared_ptr<GoalHandle> handle_cancle) {
  RCL_UNUSED(handle_cancle);
  RCLCPP_INFO(get_logger(), "Cancle action.");

  return rclcpp_action::CancelResponse::ACCEPT;
}

void MoveCircleServer::HandleAccept(
    const std::shared_ptr<GoalHandle> handle_accept) {
  RCLCPP_INFO(get_logger(), "Accept action.");

  std::thread t(
      std::bind(&MoveCircleServer::executor, this, std::placeholders::_1),
      handle_accept);
  t.detach();
}

void MoveCircleServer::executor(const std::shared_ptr<GoalHandle> handle) {
  auto goal = handle->get_goal();
  auto feedback = std::make_shared<CustomAction::Feedback>();
  auto result = std::make_shared<CustomAction::Result>();

  rclcpp::Rate rate(1);
  for (int i = 0; i <= 360; i += 30) {
    if (handle->is_canceling()) {
      result->result = false;
      handle->canceled(result);
      RCLCPP_INFO(get_logger(), "Goal cancled.");
      return;
    }

    feedback->feedback = i;
    handle->publish_feedback(feedback);
    RCLCPP_INFO(get_logger(), "Feedback state: %d", i);

    rate.sleep();
  }

  if (rclcpp::ok()) {
    result->result = true;
    handle->succeed(result);
    RCLCPP_INFO(get_logger(), "Finished.");
  }
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<MoveCircleServer>());

  rclcpp::shutdown();

  return 0;
}