#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

class JoyToAckermannBridge : public rclcpp::Node
{
public:
    JoyToAckermannBridge()
    : Node("joy_to_ackermann_bridge")
    {
        joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "/joy", 10,
            std::bind(&JoyToAckermannBridge::joyCallback, this, std::placeholders::_1)
        );

        cmd_pub_ = this->create_publisher<geometry_msgs::msg::TwistStamped>(
            "/ackermann_controller_velocity/reference", 10
        );
    }

private:
    void joyCallback(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        geometry_msgs::msg::TwistStamped cmd_msg;
        cmd_msg.header.stamp = this->get_clock()->now();
        cmd_msg.header.frame_id = "base_link";

        // Example: axis 1 for forward/backward, axis 2 for left/right
        if (msg->axes.size() >= 2) {
            cmd_msg.twist.linear.x = msg->axes[1] * max_speed_*-1;         // Forward/Backward
            cmd_msg.twist.angular.z = msg->axes[2] * max_steering_angle_*-1; // Left/Right steering
        }

        cmd_pub_->publish(cmd_msg);
    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr cmd_pub_;

    // Parameters you can tweak
    const double max_speed_ = 2.0;            // [m/s] maximum speed
    const double max_steering_angle_ = 0.6;   // [rad] maximum steering angle
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JoyToAckermannBridge>());
    rclcpp::shutdown();
    return 0;
}
