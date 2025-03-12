#include <rclcpp/rclcpp.hpp>

#include <interface/srv/add_two_num.hpp>

class AddTwoNumClient : public rclcpp::Node {
public:
  AddTwoNumClient();
  ~AddTwoNumClient();

  int64_t AddTwoNum(int64_t a, int64_t b);

private:
  rclcpp::Client<interface::srv::AddTwoNum>::SharedPtr client_;
};