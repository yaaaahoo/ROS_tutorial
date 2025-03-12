cmake_minimum_required(VERSION 3.8)
project(learning_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs)
find_package(std_srvs)
find_package(interface)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(include/learning_service)

add_executable(spawn_turtle_node src/spawn_turtle_client.cpp)
ament_target_dependencies(spawn_turtle_node rclcpp turtlesim)
install(TARGETS
  spawn_turtle_node
  DESTINATION lib/${PROJECT_NAME})

add_executable(control_turtle_node src/control_turtle_server.cpp)
ament_target_dependencies(control_turtle_node rclcpp geometry_msgs std_srvs)
install(TARGETS
  control_turtle_node
  DESTINATION lib/${PROJECT_NAME})

add_executable(add_two_num_client src/add_two_num_client.cpp)
ament_target_dependencies(add_two_num_client rclcpp interface)
install(TARGETS
  add_two_num_client
  DESTINATION lib/${PROJECT_NAME})

add_executable(add_two_num_server src/add_two_num_server.cpp)
ament_target_dependencies(add_two_num_server rclcpp interface)
install(TARGETS
  add_two_num_server
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
