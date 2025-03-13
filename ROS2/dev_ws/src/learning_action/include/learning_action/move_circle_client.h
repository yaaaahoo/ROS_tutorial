#include "interface/action/move_circle.hpp"
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

class MoveCircleClient : public rclcpp::Node {
public:
  using CustomAction = interface::action::MoveCircle;
  using GoalHandle = rclcpp_action::ClientGoalHandle<CustomAction>;

  explicit MoveCircleClient(
      const rclcpp::NodeOptions &options = rclcpp::NodeOptions(),
      const std::string &name = "move_circle_node");
  ~MoveCircleClient();

  void SendGoal(bool enable);
  void CancleGoal();

private:
  void ResponseCallback(GoalHandle::SharedPtr goal_msg);
  void
  FeedbackCallback(GoalHandle::SharedPtr goal_msg,
                   std::shared_ptr<const CustomAction::Feedback> feedback_msg);
  void FinishCallback(const GoalHandle::WrappedResult &res);

private:
  rclcpp_action::Client<interface::action::MoveCircle>::SharedPtr client_;
  GoalHandle::SharedPtr goal_handle_;
  rclcpp::TimerBase::SharedPtr timer_;
};