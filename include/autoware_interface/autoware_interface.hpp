#ifndef AUTOWARE_INTERFACE__AUTOWARE_INTERFACE_HPP_
#define AUTOWARE_INTERFACE__AUTOWARE_INTERFACE_HPP_

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
#include "sensor_msgs/msg/imu.hpp"

#include <chrono>
#include <cmath>

#define KPH2MPS 1/3.6
#define SOUL_WHEEL_BASE 2.57048
#define DEG2RAD 0.0174533
#define WHEEL_SPEED_RATIO 0.03125

namespace autoware_interface_ns
{

class AutowareInterface : public rclcpp::Node
{
    public:
        explicit AutowareInterface(const rclcpp::NodeOptions & node_options);

    private:
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr TC_throttle_command_sub_; 
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr TC_brake_command_sub_; 
        rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr TC_steering_command_sub_; 
        rclcpp::Subscription<autoware_auto_control_msgs::msg::AckermannControlCommand>::SharedPtr autoware_command_sub_;
        rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr CAN_sub_;

        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr TC_velocity_status_pub_;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr TC_steering_status_pub_;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr TC_velocity_cmd_pub_;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr TC_steer_cmd_pub_;
        rclcpp::Publisher<autoware_auto_vehicle_msgs::msg::VelocityReport>::SharedPtr velocity_status_pub_;
        rclcpp::Publisher<autoware_auto_vehicle_msgs::msg::SteeringReport>::SharedPtr steer_status_pub_;
        rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr steer_vel_pub_matlab_;
        rclcpp::Publisher<roscco_msgs::msg::ThrottleCommand>::SharedPtr roscco_throttle_cmd_pub_;
        rclcpp::Publisher<roscco_msgs::msg::BrakeCommand>::SharedPtr roscco_brake_cmd_pub_;
        rclcpp::Publisher<roscco_msgs::msg::SteeringCommand>::SharedPtr roscco_steer_cmd_pub_;

        rclcpp::TimerBase::SharedPtr timer_;

        autoware_auto_vehicle_msgs::msg::SteeringReport steer_msg_;
        autoware_auto_vehicle_msgs::msg::VelocityReport velocity_msg_;

        std_msgs::msg::Float64 velocity_matlab_msg;
        std_msgs::msg::Float64 steer_matlab_msg;
        std_msgs::msg::Float64 steer_vel_matlab_msg;
        std_msgs::msg::Float64 velocity_command_msg;
        std_msgs::msg::Float64 steer_command_msg;

        double TC_throttle_cmd; 
        double TC_brake_cmd; 
        double TC_steer_cmd; 

        roscco_msgs::msg::ThrottleCommand roscco_throttle_msg;
        roscco_msgs::msg::BrakeCommand roscco_brake_msg;
        roscco_msgs::msg::SteeringCommand roscco_steering_msg;

        void CANCallback(const can_msgs::msg::Frame::SharedPtr msg);
        void TCthrottlecmdCallback(const std_msgs::msg::Float64::SharedPtr msg);
        void TCsteercmdCallback(const std_msgs::msg::Float64::SharedPtr msg);
        void TCbrakecmdCallback(const std_msgs::msg::Float64::SharedPtr msg);
        void timer_callback();
        void AWcmdcallback(const autoware_auto_control_msgs::msg::AckermannControlCommand::SharedPtr msg);
        void CM_IMU_callback(const sensor_msgs::msg::Imu::SharedPtr msg);
        void pubMarker(const sensor_msgs::msg::Imu point);
};
}
#endif  // AUTOWARE_INTERFACE__AUTOWARE_INTERFACE_HPP_