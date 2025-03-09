#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <turtlesim/Spawn.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "turtle_tf_listener");

  // 创建 turtle2
  ros::NodeHandle h;
  ros::service::waitForService("/spawn");
  auto client = h.serviceClient<turtlesim::Spawn>("/spawn");
  turtlesim::Spawn srv;
  client.call(srv);

  // 创建速度指令的发布者
  auto pub = h.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);

  // 创建 tf 监听者
  tf::TransformListener listener;

  ros::Rate rate(10);
  while (ros::ok()) {
    tf::StampedTransform transform;
    try {
      // 这里是希望把turtle1的位置信息转变为turtle2的位置信息
      // 所以 target_frame 是turtle2，source_frame 是turtle1
      std::string target_frame = "/turtle2";
      std::string source_frame = "/turtle1";
      listener.waitForTransform(target_frame, source_frame, ros::Time(0),
                                ros::Duration(3.0));
      listener.lookupTransform(target_frame, source_frame, ros::Time(0),
                               transform);
    } catch (const ros::Exception &e) {
      ROS_ERROR("exception: %s.\n", e.what());
      return -1;
    }

    // 这里做了欧式变换获得速度...
    // 这里的计算不同，会有不同的运动效果
    // 现在是保证turtle2朝着turtle1的位置前进
    geometry_msgs::Twist msg;
    msg.angular.z =
        4.0 * atan2(transform.getOrigin().y(), transform.getOrigin().x());
    msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) +
                              pow(transform.getOrigin().y(), 2));
    pub.publish(msg);

    rate.sleep();
  }

  return 0;
}