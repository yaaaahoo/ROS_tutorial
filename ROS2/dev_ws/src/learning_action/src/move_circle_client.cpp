#include "move_circle_client.h"

#include <future>
#include <signal.h>

MoveCircleClient::MoveCircleClient(const rclcpp::NodeOptions &options,
                                   const std::string &name)
    : rclcpp::Node(name, options) {
  RCLCPP_INFO(get_logger(), "MoveCircleClient Constructor.");

  client_ = rclcpp_action::create_client<CustomAction>(
      this->get_node_base_interface(), this->get_node_graph_interface(),
      this->get_node_logging_interface(), this->get_node_waitables_interface(),
      "/move_circle");
}

MoveCircleClient::~MoveCircleClient() {
  RCLCPP_INFO(get_logger(), "MoveCircleClient DeConstructor.");
}

void MoveCircleClient::SendGoal(bool enable) {
  // 检查动作服务器是否可用
  if (!client_->wait_for_action_server(std::chrono::seconds(10))) {
    RCLCPP_ERROR(get_logger(), "Action server is not ready. Shutdown.");
    rclcpp::shutdown();
    return;
  }

  RCLCPP_INFO(get_logger(), "Action server is ready.");

  // 绑定动作目标响应回调函数、反馈回调函数、结果回调函数
  rclcpp_action::Client<CustomAction>::SendGoalOptions goal_options;
  goal_options.goal_response_callback = std::bind(
      &MoveCircleClient::ResponseCallback, this, std::placeholders::_1);
  goal_options.feedback_callback =
      std::bind(&MoveCircleClient::FeedbackCallback, this,
                std::placeholders::_1, std::placeholders::_2);
  goal_options.result_callback =
      std::bind(&MoveCircleClient::FinishCallback, this, std::placeholders::_1);

  // 创建目标数据
  auto goal_msg = CustomAction::Goal();
  goal_msg.enable = enable;

  // 异步发送目标
  RCLCPP_INFO(get_logger(), "Send goal msg...");
  auto future_goal_handle = client_->async_send_goal(goal_msg, goal_options);
  if (future_goal_handle.wait_for(std::chrono::seconds(1)) ==
      std::future_status::ready) {
    goal_handle_ = future_goal_handle.get();
  }
}

void MoveCircleClient::ResponseCallback(GoalHandle::SharedPtr goal_msg) {
  if (!goal_msg) {
    RCLCPP_ERROR(get_logger(), "Goal was rejected by server.");
    rclcpp::shutdown();
    return;
  }

  RCLCPP_INFO(get_logger(), "Goal accepted by server, waiting result...");
}

void MoveCircleClient::FeedbackCallback(
    GoalHandle::SharedPtr goal_msg,
    std::shared_ptr<const CustomAction::Feedback> feedback_msg) {
  RCL_UNUSED(goal_msg);

  RCLCPP_INFO(get_logger(), "Recieve feedback: %d", feedback_msg->feedback);
}

void MoveCircleClient::FinishCallback(const GoalHandle::WrappedResult &res) {

  switch (res.code) {
  case rclcpp_action::ResultCode::SUCCEEDED:
    break;
  case rclcpp_action::ResultCode::ABORTED:
    RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
    rclcpp::shutdown();
    return;
  case rclcpp_action::ResultCode::CANCELED:
    RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
    rclcpp::shutdown();
    return;
  default:
    RCLCPP_ERROR(this->get_logger(), "Unknown result code");
    rclcpp::shutdown();
    return;
  }

  RCLCPP_INFO(get_logger(), "Finished. result: %d",
              static_cast<int>(res.result->result));
  rclcpp::shutdown();
}

void MoveCircleClient::CancleGoal() {
  // 取消 goal
  RCLCPP_INFO(get_logger(), "Cancle goal...");

  auto res_future = client_->async_cancel_goal(goal_handle_);

  // 处理取消操作后的 server 响应
  if (res_future.wait_for(std::chrono::seconds(1)) ==
      std::future_status::ready) {
    auto cancle_res = res_future.get();
    switch (cancle_res->return_code) {
    case action_msgs::srv::CancelGoal_Response::ERROR_NONE:
      RCLCPP_INFO(get_logger(), "Cancle succeeded.");
      break;
    case action_msgs::srv::CancelGoal_Response::ERROR_REJECTED:
      RCLCPP_WARN(get_logger(), "Cancle rejected.");
      break;
    case action_msgs::srv::CancelGoal_Response::ERROR_UNKNOWN_GOAL_ID:
      RCLCPP_ERROR(get_logger(), "Goal does not exist.");
      break;
    case action_msgs::srv::CancelGoal_Response::ERROR_GOAL_TERMINATED:
      RCLCPP_ERROR(get_logger(), "Goal has been cancled.");
      break;
    default:
      break;
    }
  }
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  bool enable = true;
  auto node_ptr = std::make_shared<MoveCircleClient>();
  if (argc < 2) {
    RCLCPP_WARN(node_ptr->get_logger(),
                "Need param to enable send goal. Default is true.");
  } else {
    enable = static_cast<bool>(atoi(argv[1]));
  }
  node_ptr->SendGoal(enable);

  rclcpp::spin(node_ptr);

  rclcpp::shutdown();

  return 0;
}