#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

std::string turtle_name = "";

void CallbackFunc(const turtlesim::Pose::ConstPtr &pose) {
  //   ROS_INFO("[%s] call CallbackFunc.\n", turtle_name.c_str());

  // 创建 tf 广播器
  static tf::TransformBroadcaster broadcaster;

  // 初始化广播数据
  tf::Transform data;
  data.setOrigin(tf::Vector3(pose->x, pose->y, 0.0));
  tf::Quaternion q;
  q.setRPY(0.0, 0.0, pose->theta);
  data.setRotation(q);

  // 广播 world 坐标系与 turtle_name 坐标系之间的 tf 数据
  broadcaster.sendTransform(
      tf::StampedTransform(data, ros::Time::now(), "world", turtle_name));
}

int main(int argc, char **argv) {
  /**这里的init动作必须在参数数量判断前，不然会有解析错误**/
  ros::init(argc, argv, "turtle_tf_broadcaster");

  if (argc != 2) {
    ROS_ERROR("need turtle name as param.\n");
    return -1;
  }

  turtle_name = argv[1];

  ros::NodeHandle h;
  auto sub =
      h.subscribe<turtlesim::Pose>(turtle_name + "/pose", 10, CallbackFunc);

  ros::spin();

  return 0;
}