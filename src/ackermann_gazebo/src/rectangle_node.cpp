#include <chrono>
#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class RectangleTrajectory : public rclcpp::Node 
{
public:
    RectangleTrajectory() : Node("rectangle_trajectory"), state_(0) 
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        // 设置 100ms (10Hz) 的控制频率
        timer_ = this->create_wall_timer(100ms, std::bind(&RectangleTrajectory::timer_callback, this));
        
        // 记录节点启动的时间
        start_time_ = this->now();
        RCLCPP_INFO(this->get_logger(), "开始执行矩形轨迹任务...");
    }

private:
    void timer_callback() 
    {
        auto msg = geometry_msgs::msg::Twist();
        auto current_time = this->now();
        // 计算在当前状态下已经经过了多少秒
        double elapsed = (current_time - start_time_).seconds();

        // 状态机逻辑
        if (state_ == 0) {
            // 状态 0：以 0.5m/s 前进 10m (需 20 秒)
            msg.linear.x = 0.5;
            msg.angular.z = 0.0;
            if (elapsed > 20.0) next_state();
            
        } else if (state_ == 1) {
            // 状态 1：向右拐 90 度 (需 3.14 秒)
            msg.linear.x = 0.5;
            msg.angular.z = -0.5; // 负数代表右转
            if (elapsed > 3.14) next_state();
            
        } else if (state_ == 2) {
            // 状态 2：拐弯后以 0.6m/s 前进 6m (需 10 秒)
            msg.linear.x = 0.6;
            msg.angular.z = 0.0;
            if (elapsed > 10.0) next_state();
            
        } else if (state_ == 3) {
            // 状态 3：向右拐 90 度 (需 3.14 秒)
            msg.linear.x = 0.5;
            msg.angular.z = -0.5;
            if (elapsed > 3.14) next_state();
            
        } else if (state_ == 4) {
            // 状态 4：以 0.5m/s 前进 10m (需 20 秒)
            msg.linear.x = 0.5;
            msg.angular.z = 0.0;
            if (elapsed > 20.0) next_state();
            
        } else if (state_ == 5) {
            // 状态 5：向右拐 90 度 (需 3.14 秒)
            msg.linear.x = 0.5;
            msg.angular.z = -0.5;
            if (elapsed > 3.14) next_state();
            
        } else if (state_ == 6) {
            // 状态 6：以 0.6m/s 前进 6m，走完最后一条边回到原点 (需 10 秒)
            msg.linear.x = 0.6;
            msg.angular.z = 0.0;
            if (elapsed > 10.0) next_state();
            
        } else {
            // 状态 7：任务完成，停车
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
            RCLCPP_INFO_ONCE(this->get_logger(), "已回到起点附近，任务结束，停车！");
        }

        // 发送速度指令
        publisher_->publish(msg);
    }

    // 切换到下一个状态，并重置计时器
    void next_state() {
        state_++;
        start_time_ = this->now();
        RCLCPP_INFO(this->get_logger(), "切换到阶段 %d", state_);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Time start_time_;
    int state_; // 记录当前运行到哪一步了
};

int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RectangleTrajectory>());
    rclcpp::shutdown();
    return 0;
}