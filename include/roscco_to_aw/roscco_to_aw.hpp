#ifndef ROSCCO__ROSCCO_TO_AW_HPP_
#define ROSCCO__ROSCCO_TO_AW_HPP_

#include <rclcpp/rclcpp.hpp>
#include <memory>
#include "roscco_msgs/msg/brake_command.hpp"
#include "roscco_msgs/msg/throttle_command.hpp"
#include "roscco_msgs/msg/steering_command.hpp"
#include "autoware_auto_vehicle_msgs/msg/steering_report.hpp"
#include "autoware_auto_vehicle_msgs/msg/velocity_report.hpp"
#include "autoware_auto_control_msgs/msg/ackermann_control_command.hpp"
#include "std_msgs/msg/float64.hpp"
#include "can_msgs/msg/frame.hpp"
#include <chrono>
#include <cmath>

#define KPH2MPS 1/3.6
#define SOUL_WHEEL_BASE 2.57048
#define DEG2RAD 0.0174533
#define WHEEL_SPEED_RATIO 0.03125

namespace roscco_component
{

class RosccoToAW : public rclcpp::Node
{
    public:
        explicit RosccoToAW(const rclcpp::NodeOptions & node_options);

    private:
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr topic_throttle_command_matlab_; // HJK
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr topic_brake_command_matlab_; // HJK
        rclcpp::Subscription<autoware_auto_control_msgs::msg::AckermannControlCommand>::SharedPtr sub_autoware_linear_command_;
        rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr sub_can_;

        rclcpp::Publisher<autoware_auto_vehicle_msgs::msg::SteeringReport>::SharedPtr steer_pub_;
        rclcpp::Publisher<autoware_auto_vehicle_msgs::msg::VelocityReport>::SharedPtr velocity_pub_;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr velocity_pub_matlab_;
        rclcpp::Publisher<roscco_msgs::msg::ThrottleCommand>::SharedPtr throttle_cmd_pub_;
        rclcpp::Publisher<roscco_msgs::msg::BrakeCommand>::SharedPtr brake_cmd_pub_;
        rclcpp::Publisher<roscco_msgs::msg::SteeringCommand>::SharedPtr steer_cmd_pub_;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr velocity_cmd_pub_;

        rclcpp::TimerBase::SharedPtr timer_;

        autoware_auto_vehicle_msgs::msg::SteeringReport steer_msg_;
        autoware_auto_vehicle_msgs::msg::VelocityReport velocity_msg_;
        std_msgs::msg::Float64 velocity_matlab_msg;
        std_msgs::msg::Float64 velocity_command_msg;

        double throttle; 
        double brake; 
        double steering; 
        double angle; 
        float velocity_command;
        int direction;
        double speed_report;

        roscco_msgs::msg::ThrottleCommand roscco_throttle_msg;
        roscco_msgs::msg::BrakeCommand roscco_brake_msg;
        roscco_msgs::msg::SteeringCommand roscco_steering_msg;

        void topic_callback(const can_msgs::msg::Frame::SharedPtr msg);
        void throttleMLCommandCallback(const std_msgs::msg::Float64::SharedPtr msg);
        void brakeMLCommandCallback(const std_msgs::msg::Float64::SharedPtr msg);
        void timer_callback();
        void aw_callback(const autoware_auto_control_msgs::msg::AckermannControlCommand::SharedPtr msg);
};
}
#endif  // ROSCCO__ROSCCO_TO_AW_HPP_
