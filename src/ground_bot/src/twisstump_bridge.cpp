#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

class TwistToTwistStampedBridge : public rclcpp::Node
{
public:
    TwistToTwistStampedBridge()
    : Node("twist_to_twiststamped_bridge")
    {
        sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel", 10,
            std::bind(&TwistToTwistStampedBridge::cmdVelCallback, this, std::placeholders::_1)
        );

        pub_ = this->create_publisher<geometry_msgs::msg::TwistStamped>(
            "/ackermann_controller_velocity/reference", 10
        );
    }

private:
    void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        geometry_msgs::msg::TwistStamped stamped_msg;
        stamped_msg.header.stamp = this->get_clock()->now();
        stamped_msg.header.frame_id = "base_link";
        stamped_msg.twist = *msg;
        pub_->publish(stamped_msg);
    }

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_;
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TwistToTwistStampedBridge>());
    rclcpp::shutdown();
    return 0;
}

