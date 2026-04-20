cmake_minimum_required(VERSION 3.8)
project(ackermann_gazebo)

find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

# 编译 C++ 节点
add_executable(topic_pub_cpp src/topic_pub_cpp.cpp)
ament_target_dependencies(
  topic_pub_cpp
  "rclcpp"
  "geometry_msgs"
)

# 安装到 lib 目录
install(TARGETS topic_pub_cpp
  DESTINATION lib/${PROJECT_NAME})

# 编译选项
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

# 安装资源目录
install(DIRECTORY
  launch
  urdf
  worlds
  DESTINATION share/${PROJECT_NAME}
)

# 这一行是 CMake 文件的终点
ament_package()