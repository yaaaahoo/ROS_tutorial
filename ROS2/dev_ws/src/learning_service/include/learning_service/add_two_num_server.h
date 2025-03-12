#include <interface/srv/add_two_num.hpp>
#include <rclcpp/rclcpp.hpp>

class AddTwoNumServer : public rclcpp::Node {
public:
  AddTwoNumServer();
  ~AddTwoNumServer();

  void callback(std::shared_ptr<interface::srv::AddTwoNum::Request> req,
                std::shared_ptr<interface::srv::AddTwoNum::Response> res);

private:
  rclcpp::Service<interface::srv::AddTwoNum>::SharedPtr server_;
};