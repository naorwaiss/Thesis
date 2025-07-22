#ifndef JOINT_WRENCH_PLUGIN_HPP
#define JOINT_WRENCH_PLUGIN_HPP

#include <ignition/gazebo/System.hh>
#include <ignition/gazebo/Model.hh>
#include <ignition/gazebo/components/Joint.hh>
#include <ignition/gazebo/components/JointForce.hh>
#include <ignition/gazebo/components/JointVelocity.hh>
#include <ignition/gazebo/components/JointPosition.hh>
#include <ignition/transport/Node.hh>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/wrench_stamped.hpp>
#include <memory>

namespace gazebo_plugins
{
  class JointWrenchPlugin : public ignition::gazebo::System,
                           public ignition::gazebo::ISystemConfigure,
                           public ignition::gazebo::ISystemPostUpdate
  {
  public:
    void Configure(const ignition::gazebo::Entity &_entity,
                   const std::shared_ptr<const sdf::Element> &_sdf,
                   ignition::gazebo::EntityComponentManager &_ecm,
                   ignition::gazebo::EventManager &_eventMgr) override;

    void PostUpdate(const ignition::gazebo::UpdateInfo &_info,
                    const ignition::gazebo::EntityComponentManager &_ecm) override;

  private:
    ignition::gazebo::Model model_{ignition::gazebo::kNullEntity};
    ignition::gazebo::Entity joint_entity_{ignition::gazebo::kNullEntity};

    std::shared_ptr<rclcpp::Node> ros_node_;
    rclcpp::Publisher<geometry_msgs::msg::WrenchStamped>::SharedPtr wrench_pub_;

    std::string joint_name_;
    std::string topic_name_;
  };
}

#endif

