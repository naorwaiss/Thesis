#ifndef PUB_HPP
#define PUB_HPP

#include "Var_type.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class pub : public rclcpp::Node {
   public:
    pub();
    void publish();

   private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    std::string message;
};
#endif
