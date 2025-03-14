cmake_minimum_required(VERSION 3.8)
project(learning_topic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(interface)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(include/learning_topic)

add_executable(vel_topic_pub_node src/vel_topic_pub.cpp)
ament_target_dependencies(vel_topic_pub_node rclcpp geometry_msgs)
install(TARGETS
  vel_topic_pub_node
  DESTINATION lib/${PROJECT_NAME})

add_executable(pose_topic_sub_node src/pose_topic_sub.cpp)
ament_target_dependencies(pose_topic_sub_node rclcpp turtlesim)
install(TARGETS
  pose_topic_sub_node
  DESTINATION lib/${PROJECT_NAME})

add_executable(room_env_pub src/room_env_pub.cpp)
ament_target_dependencies(room_env_pub rclcpp interface)
install(TARGETS
room_env_pub
  DESTINATION lib/${PROJECT_NAME})

add_executable(room_env_sub src/room_env_sub.cpp)
ament_target_dependencies(room_env_sub rclcpp interface)
install(TARGETS
room_env_sub
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
