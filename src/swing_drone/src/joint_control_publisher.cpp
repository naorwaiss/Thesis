#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class JointControlPublisher : public rclcpp::Node
{
public:
    JointControlPublisher()
    : Node("joint_control_publisher")
    {
        publisher_ = this->create_publisher<std_msgs::msg::Bool>("/joint_control", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&JointControlPublisher::publish_message, this));
    }

private:
    void publish_message()
    {
        auto message = std_msgs::msg::Bool();
        message.data = false;  // Set the message data to false
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data ? "true" : "false");
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JointControlPublisher>());
    rclcpp::shutdown();
    return 0;
} 