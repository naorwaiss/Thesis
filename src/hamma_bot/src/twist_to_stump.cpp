#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <geometry_msgs/msg/twist.hpp>

class TwistToTwistStampedNode : public rclcpp::Node
{
public:
    TwistToTwistStampedNode()
    : Node("twist_to_twist_stamped_node")
    {
        // Subscriber to Twist
        twist_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel", 10,
            std::bind(&TwistToTwistStampedNode::twistCallback, this, std::placeholders::_1)
        );

        // Publisher for TwistStamped
        twist_stamped_pub_ = this->create_publisher<geometry_msgs::msg::TwistStamped>(
            "/twist_stamped_out", 10
        );

        RCLCPP_INFO(this->get_logger(), "TwistToTwistStampedNode started");
    }

private:
    void twistCallback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        geometry_msgs::msg::TwistStamped twist_stamped_msg;

        // Fill header (timestamp and optionally frame_id)
        twist_stamped_msg.header.stamp = this->now();
        twist_stamped_msg.header.frame_id = "base_link"; // << you can change if needed

        // Copy linear and angular data
        twist_stamped_msg.twist.linear = msg->linear;
        twist_stamped_msg.twist.angular = msg->angular;

        twist_stamped_pub_->publish(twist_stamped_msg);
    }

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_sub_;
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr twist_stamped_pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TwistToTwistStampedNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
