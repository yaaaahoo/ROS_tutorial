#include "interface/action/move_circle.hpp"
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

class MoveCircleServer : public rclcpp::Node {
public:
  using CustomAction = interface::action::MoveCircle;
  using GoalHandle = rclcpp_action::ServerGoalHandle<CustomAction>;

  explicit MoveCircleServer(rclcpp::NodeOptions options = rclcpp::NodeOptions(),
                            const std::string &name = "move_circle_server");
  ~MoveCircleServer();

private:
  rclcpp_action::GoalResponse
  HandleGoal(const rclcpp_action::GoalUUID &uuid,
             std::shared_ptr<const CustomAction::Goal> goal_req);
  rclcpp_action::CancelResponse
  HandleCancle(const std::shared_ptr<GoalHandle> handle_cancle);
  void HandleAccept(const std::shared_ptr<GoalHandle> handle_accept);

  void executor(const std::shared_ptr<GoalHandle> handle);

private:
  rclcpp_action::Server<CustomAction>::SharedPtr server_;
};