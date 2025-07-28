#include <gz/plugin/Register.hh>
#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Joint.hh>
#include <gz/sim/components/Joint.hh>
#include <gz/sim/components/JointPosition.hh>
#include <gz/sim/components/JointVelocity.hh>
#include <gz/sim/components/JointForce.hh>
#include <gz/sim/components/JointVelocityCmd.hh>
#include <gz/sim/components/Name.hh>
#include <gz/sim/EntityComponentManager.hh>
#include <gz/sim/EventManager.hh>
#include <gz/transport/Node.hh>
#include <gz/msgs/joint_wrench.pb.h>
#include <gz/msgs/boolean.pb.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/bool.hpp>
#include <chrono>
#include <map>
#include <string>
#include <vector>

namespace swing_drone
{
    class JointControllerPlugin : public gz::sim::System,
                                  public gz::sim::ISystemConfigure,
                                  public gz::sim::ISystemPreUpdate,
                                  public gz::sim::ISystemPostUpdate
    {
    private:
        // ROS 2 node and publishers/subscribers
        rclcpp::Node::SharedPtr ros_node_;
        rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr joint_control_sub_;
        
        // Gazebo transport for joint control
        gz::transport::Node gz_node_;
        
        // Joint entities and names
        std::vector<std::string> joint_names_ = {"fr_joint", "fl_joint", "br_joint", "bl_joint"};
        std::map<std::string, gz::sim::Entity> joint_entities_;
        
        // Control state
        bool joints_free_ = true; // true = free spinning, false = fixed
        bool last_joints_state_ = true; // Track previous state to avoid spam
        
        // Timing
        std::chrono::steady_clock::time_point last_publish_time_;
        std::chrono::milliseconds publish_period_{10}; // 100 Hz publishing rate
        
        // Model entity
        gz::sim::Entity model_entity_;
        
    public:
        void Configure(const gz::sim::Entity &entity,
                      const std::shared_ptr<const sdf::Element> &sdf,
                      gz::sim::EntityComponentManager &ecm,
                      gz::sim::EventManager &eventMgr) override
        {
            (void)sdf;      // Suppress unused parameter warning
            (void)eventMgr; // Suppress unused parameter warning
            
            // Initialize ROS 2 node
            if (!rclcpp::ok())
            {
                rclcpp::init(0, nullptr);
            }
            
            ros_node_ = rclcpp::Node::make_shared("joint_controller_plugin");
            
            // Create publisher for joint states
            joint_state_pub_ = ros_node_->create_publisher<sensor_msgs::msg::JointState>(
                "arm_joint_states", 10);
            
            // Create subscriber for joint control
            joint_control_sub_ = ros_node_->create_subscription<std_msgs::msg::Bool>(
                "joint_control", 10,
                [this](const std_msgs::msg::Bool::SharedPtr msg) {
                    joints_free_ = msg->data;
                    // RCLCPP_INFO(ros_node_->get_logger(), 
                    //     "Joint control changed: %s", joints_free_ ? "FREE" : "FIXED");
                });
            
            // Store model entity
            model_entity_ = entity;
            
            // Get joint entities
            for (const auto& joint_name : joint_names_)
            {
                auto joint_entity = ecm.EntityByComponents(
                    gz::sim::components::Joint(),
                    gz::sim::components::Name(joint_name));
                
                if (joint_entity != gz::sim::kNullEntity)
                {
                    joint_entities_[joint_name] = joint_entity;
                    
                    // Enable position, velocity, and force components
                    ecm.CreateComponent(joint_entity, gz::sim::components::JointPosition());
                    ecm.CreateComponent(joint_entity, gz::sim::components::JointVelocity());
                    ecm.CreateComponent(joint_entity, gz::sim::components::JointForce());
                    
                    // RCLCPP_INFO(ros_node_->get_logger(), 
                    //     "Found joint: %s", joint_name.c_str());
                }
                else
                {
                    // RCLCPP_WARN(ros_node_->get_logger(), 
                    //     "Could not find joint: %s", joint_name.c_str());
                }
            }
            
            last_publish_time_ = std::chrono::steady_clock::now();
            
            // RCLCPP_INFO(ros_node_->get_logger(), 
            //     "Joint Controller Plugin initialized with %zu joints", 
            //     joint_entities_.size());
        }
        
        void PreUpdate(const gz::sim::UpdateInfo &info,
                      gz::sim::EntityComponentManager &ecm) override
        {
            (void)info; // Suppress unused parameter warning
            
            // Log state change for all joints when the mode changes
            if (last_joints_state_ != joints_free_)
            {
                // for (const auto& [joint_name, joint_entity] : joint_entities_)
                // {
                //     RCLCPP_INFO(ros_node_->get_logger(), 
                //         "Joint %s mode: %s", joint_name.c_str(), joints_free_ ? "FREE" : "FIXED");
                // }
                last_joints_state_ = joints_free_;
            }
            
            // For now, we'll just track the mode but not apply aggressive control
            // The aggressive damping was causing physics instability
            // In FREE mode, joints can move naturally
            // In FIXED mode, we could apply very light damping or just track the state
            
            for (const auto& [joint_name, joint_entity] : joint_entities_)
            {
                if (!joints_free_)
                {
                    // FIXED mode: Apply very gentle damping to reduce movement
                    auto vel_cmd = ecm.Component<gz::sim::components::JointVelocityCmd>(joint_entity);
                    if (!vel_cmd)
                    {
                        ecm.CreateComponent(joint_entity, gz::sim::components::JointVelocityCmd({0.0}));
                    }
                    else if (vel_cmd->Data().size() > 0)
                    {
                        auto velocity = ecm.Component<gz::sim::components::JointVelocity>(joint_entity);
                        if (velocity && velocity->Data().size() > 0)
                        {
                            // Apply very light damping - much gentler than before
                            double current_velocity = velocity->Data()[0];
                            vel_cmd->Data()[0] = -current_velocity * 0.5; // Very light damping
                        }
                    }
                }
                else
                {
                    // FREE mode: Remove any velocity commands
                    auto vel_cmd = ecm.Component<gz::sim::components::JointVelocityCmd>(joint_entity);
                    if (vel_cmd)
                    {
                        ecm.RemoveComponent<gz::sim::components::JointVelocityCmd>(joint_entity);
                    }
                }
            }
        }
        
        void PostUpdate(const gz::sim::UpdateInfo &info,
                       const gz::sim::EntityComponentManager &ecm) override
        {
            (void)info; // Suppress unused parameter warning
            
            // Spin ROS node
            rclcpp::spin_some(ros_node_);
            
            // Check if it's time to publish
            auto current_time = std::chrono::steady_clock::now();
            if (current_time - last_publish_time_ < publish_period_)
            {
                return;
            }
            last_publish_time_ = current_time;
            
            // Create and populate joint state message
            auto msg = sensor_msgs::msg::JointState();
            msg.header.stamp = ros_node_->now();
            msg.header.frame_id = "base_link";
            
            // Reserve space for the vectors to avoid reallocation
            msg.name.reserve(joint_entities_.size());
            msg.position.reserve(joint_entities_.size());
            msg.velocity.reserve(joint_entities_.size());
            msg.effort.reserve(joint_entities_.size());
            
            int valid_joints = 0;
            for (const auto& [joint_name, joint_entity] : joint_entities_)
            {
                // Get joint components with safety checks
                const auto* position = ecm.Component<gz::sim::components::JointPosition>(joint_entity);
                const auto* velocity = ecm.Component<gz::sim::components::JointVelocity>(joint_entity);
                const auto* force = ecm.Component<gz::sim::components::JointForce>(joint_entity);
                
                // Add data (even if components are not ready, use default values)
                msg.name.push_back(joint_name);
                
                if (position && !position->Data().empty())
                {
                    msg.position.push_back(position->Data()[0]);
                }
                else
                {
                    msg.position.push_back(0.0);
                }
                
                if (velocity && !velocity->Data().empty())
                {
                    msg.velocity.push_back(velocity->Data()[0]);
                }
                else
                {
                    msg.velocity.push_back(0.0);
                }
                
                if (force && !force->Data().empty())
                {
                    msg.effort.push_back(force->Data()[0]);
                }
                else
                {
                    msg.effort.push_back(0.0);
                }
                
                valid_joints++;
            }
            
            // Always publish, even with default values
            if (valid_joints > 0)
            {
                joint_state_pub_->publish(msg);
                
                // Debug log every 100 publishes (every 1 second at 100Hz)
                static int publish_count = 0;
                publish_count++;
                if (publish_count % 100 == 0)
                {
                    // RCLCPP_INFO(ros_node_->get_logger(), 
                    //     "Published joint states for %d joints (count: %d)", valid_joints, publish_count);
                }
            }
        }
    };
}

// Register the plugin
GZ_ADD_PLUGIN(
    swing_drone::JointControllerPlugin,
    gz::sim::System,
    swing_drone::JointControllerPlugin::ISystemConfigure,
    swing_drone::JointControllerPlugin::ISystemPreUpdate,
    swing_drone::JointControllerPlugin::ISystemPostUpdate) 