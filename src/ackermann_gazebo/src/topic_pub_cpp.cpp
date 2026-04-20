#include <chrono> // 包含 C++ 标准库中的时间相关功能
#include <iostream> // 包含标准输入输出流功能
#include <memory> // 包含智能指针等内存管理功能
#include <thread> // 包含线程相关功能

#include "rclcpp/rclcpp.hpp" // 包含 ROS 2 的 C++ 客户端库
#include "geometry_msgs/msg/twist.hpp" // 包含 geometry_msgs/Twist 消息的定义
//  
using namespace std::chrono_literals; // 定义内存空间

class Talker : public rclcpp::Node // 定义一个名为 Talker 的类，继承自 rclcpp::Node
{
public:
    Talker() : Node("talker"), count_(0) // 构造函数，初始化节点名为 "talker"，并初始化 count_ 为 0
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10); // 创建一个发布者，发布 Twist 消息到 "topic_cmd_vel" 主题，队列大小为 10
        timer_ = this->create_wall_timer(1s, std::bind(&Talker::timer_callback, this)); // 创建一个定时器，每 1 秒调用一次 timer_callback 函数
    }

private:
    void timer_callback() // 定时器回调函数
    {
        auto message = geometry_msgs::msg::Twist(); // 创建一个 Twist 消息实例
        message.linear.x = 1.0; // 设置线速度的 x 分量为 1.0
        message.linear.y = 2.0; // 设置线速度的 y 分量为 2.0
        message.linear.z = 3.0; // 设置线速度的 z 分量为 3.0
        message.angular.x = 4.0; // 设置角速度的 x 分量为 4.0
        message.angular.y = 5.0; // 设置角速度的 y 分量为 5.0
        message.angular.z = 6.0; // 设置角速度的 z 分量为 6.0

        RCLCPP_INFO( // 使用 ROS 2 的日志宏打印信息
                    this->get_logger(), // 获取当前节点的日志记录器
                    "已发布 Twist message:\n" // 打印的消息内容
                    "  Linear: x = %f, y = %f, z = %f\n" // 打印线速度的 x、y、z 分量
                    "  Angular: x = %f, y = %f, z = %f", // 打印角速度的 x、y、z 分量
                    message.linear.x, message.linear.y, message.linear.z, // 线速度的 x、y、z 分量
                    message.angular.x, message.angular.y, message.angular.z // 角速度的 x、y、z 分量
                    );
                    
        publisher_->publish(message); // 发布 Twist 消息
    }

    rclcpp::TimerBase::SharedPtr timer_; // 定时器的智能指针
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; // 发布者的智能指针
    size_t count_; // 用于计数的变量（目前未使用）
};

int main(int argc, char *argv[]) // 主函数
{
    rclcpp::init(argc, argv); // 初始化 ROS 2 客户端库
    rclcpp::spin(std::make_shared<Talker>()); // 创建一个 Talker 节点并开始自旋，处理回调函数
    rclcpp::shutdown(); // 关闭 ROS 2 客户端库
    return 0; // 返回 0 表示程序正常结束
}