#include "swing_drone/joint_wrench_plugin.hpp"
#include <ignition/plugin/Register.hh>
#include <ignition/gazebo/components/Joint.hh>
#include <ignition/gazebo/components/JointForce.hh>
#include <ignition/gazebo/components/Name.hh>
#include <ignition/gazebo/Util.hh>
#include <rclcpp/rclcpp.hpp>

using namespace gazebo_plugins;

void JointWrenchPlugin::Configure(const ignition::gazebo::Entity &_entity,
                                  const std::shared_ptr<const sdf::Element> &_sdf,
                                  ignition::gazebo::EntityComponentManager &_ecm,
                                  ignition::gazebo::EventManager &/*_eventMgr*/)
{
  // Store the model entity
  this->model_ = ignition::gazebo::Model(_entity);

  if (!this->model_.Valid(_ecm))
  {
    ignerr << "[JointWrenchPlugin] Failed to initialize model" << std::endl;
    return;
  }

  // Get joint name from SDF
  if (_sdf->HasElement("joint_name"))
    this->joint_name_ = _sdf->Get<std::string>("joint_name");
  else
  {
    ignerr << "[JointWrenchPlugin] Missing <joint_name> element" << std::endl;
    return;
  }

  // Get topic name from SDF
  if (_sdf->HasElement("topic_name"))
    this->topic_name_ = _sdf->Get<std::string>("topic_name");
  else
    this->topic_name_ = "/joint_wrench";

  // Find the joint entity
  this->joint_entity_ = this->model_.JointByName(_ecm, this->joint_name_);
  if (this->joint_entity_ == ignition::gazebo::kNullEntity)
  {
    ignerr << "[JointWrenchPlugin] Joint not found: " << this->joint_name_ << std::endl;
    return;
  }

  // Create the JointForce component to enable force measurement
  _ecm.CreateComponent(this->joint_entity_, ignition::gazebo::components::JointForce());

  // Initialize ROS 2
  if (!rclcpp::ok())
    rclcpp::init(0, nullptr);
  
  this->ros_node_ = rclcpp::Node::make_shared("joint_wrench_plugin_node");

  // Create publisher
  this->wrench_pub_ = this->ros_node_->create_publisher<geometry_msgs::msg::WrenchStamped>(
    this->topic_name_, 10);

  igndbg << "[JointWrenchPlugin] Plugin initialized for joint: " << this->joint_name_ 
        << " publishing to: " << this->topic_name_ << std::endl;
}

void JointWrenchPlugin::PostUpdate(const ignition::gazebo::UpdateInfo &/*_info*/,
                                   const ignition::gazebo::EntityComponentManager &_ecm)
{
  // Only update if ROS is still running
  if (!rclcpp::ok())
    return;

  // Spin ROS node
  rclcpp::spin_some(this->ros_node_);

  // Get joint force/torque
  auto jointForce = _ecm.Component<ignition::gazebo::components::JointForce>(this->joint_entity_);
  
  if (!jointForce)
  {
    // Component should have been created in Configure, but just return if it's not there
    return;
  }

  // Create and publish wrench message
  geometry_msgs::msg::WrenchStamped msg;
  msg.header.stamp = this->ros_node_->now();
  msg.header.frame_id = this->joint_name_;

  // Set force and torque values
  const auto& forces = jointForce->Data();
  if (!forces.empty())
  {
    // For revolute joints, the force is typically a single value representing torque
    msg.wrench.torque.z = forces[0];  // Assuming rotation around Z-axis
    msg.wrench.force.x = 0.0;
    msg.wrench.force.y = 0.0;
    msg.wrench.force.z = 0.0;
    msg.wrench.torque.x = 0.0;
    msg.wrench.torque.y = 0.0;
  }

  this->wrench_pub_->publish(msg);
}

// Register the plugin with both class name and alias
IGNITION_ADD_PLUGIN(gazebo_plugins::JointWrenchPlugin,
                    ignition::gazebo::System,
                    gazebo_plugins::JointWrenchPlugin::ISystemConfigure,
                    gazebo_plugins::JointWrenchPlugin::ISystemPostUpdate)

// Add plugin alias
IGNITION_ADD_PLUGIN_ALIAS(gazebo_plugins::JointWrenchPlugin, "joint_wrench_plugin")
