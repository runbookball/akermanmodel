cmake_minimum_required(VERSION 3.8)
project(ackermann_gazebo)

# --- 1. 全局编译选项放在最前面 ---
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- 2. 集中寻找所有依赖包 ---
find_package(ament_cmake REQUIRED) # 必须放在第一位
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

# --- 3. 声明可执行文件并链接依赖 ---
# 节点 1: topic_pub_cpp
add_executable(topic_pub_cpp src/topic_pub_cpp.cpp)
ament_target_dependencies(topic_pub_cpp
  rclcpp
  geometry_msgs
)

# 节点 2: rectangle_node
add_executable(rectangle_node src/rectangle_node.cpp)
ament_target_dependencies(rectangle_node 
  rclcpp 
  geometry_msgs
)

# --- 4. 集中处理所有的安装 (Install) 规则 ---
# 安装可执行文件
install(TARGETS 
  topic_pub_cpp
  rectangle_node
  DESTINATION lib/${PROJECT_NAME}
)

# 安装资源目录
install(DIRECTORY
  launch
  urdf
  worlds
  DESTINATION share/${PROJECT_NAME}
)

# --- 5. 必须在最后一行 ---
ament_package()