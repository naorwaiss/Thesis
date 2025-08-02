#include <iostream>
#include <chrono>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "swing_drone/Var_type.hpp"
#include "swing_drone/ros2_data_graber.hpp"
#include "swing_drone/micros_lib.hpp"
#include "swing_drone/pub.hpp"
#include "swing_drone/simple_rate_mode.hpp"
#include "swing_drone/std_operation.hpp"

bool system_initialized = false;
const int LOOP_FREQUENCY_HZ = 200;  // Set desired loop frequency here
const auto LOOP_PERIOD_MICROS = std::chrono::microseconds(1000000 / LOOP_FREQUENCY_HZ);

// Global sensor data - automatically updated by ROS2
imu_data imu_data_read;
euler_angles euler_angles_read;
arm_data arm_data_read;
joy_data joy_data_read;
std_operation std_op_intce(&joy_data_read);

// ROS2 node for data collection (runs in background)
std::shared_ptr<data_graber_ros> ros2_data_graber;
std::shared_ptr<pub> pub_data;
std::thread ros2_thread;

elapsed_timer loop_timer(LOOP_FREQUENCY_HZ);

// Declare rate mode instance (will be initialized in main after pub_data is created)
std::unique_ptr<simple_rate_mode> rate_instance;

void setup() {
    std::cout << "Flight Controller Setup..." << std::endl;
    system_initialized = true;
    std::cout << "Flight Controller Setup Complete!" << std::endl;
    std::cout << "Running main loop at " << LOOP_FREQUENCY_HZ << " Hz" << std::endl;
}

void loop() {
    if (!system_initialized) return;

    if (loop_timer.has_elapsed()) {
        switch (std_op_intce.mode_switch()) {
            case drone_mod::rate_mode:
                if (rate_instance != nullptr) {
                    rate_instance->run_rate_mode();
                    break;
                    case drone_mod::backstepping:
                        break;
                }

                loop_timer.reset();
        }
    } else {
        printf("Waiting for data...\n");
    }
}

int main(int argc, char** argv) {
    // Initialize ROS2 (hidden from Arduino-like code)
    rclcpp::init(argc, argv);

    // Create ROS2 data grabber node
    ros2_data_graber = std::make_shared<data_graber_ros>(&imu_data_read, &euler_angles_read, &arm_data_read, &joy_data_read);
    pub_data = std::make_shared<pub>();
    rate_instance = std::make_unique<simple_rate_mode>(pub_data.get(), &imu_data_read, &joy_data_read, LOOP_FREQUENCY_HZ);

    // Create rate mode instance after pub_data is initialized

    // Start ROS2 in background thread (like Arduino's background processes)
    ros2_thread = std::thread([]() {
        try {
            // Create multi-threaded executor for both nodes
            rclcpp::executors::MultiThreadedExecutor executor;
            executor.add_node(ros2_data_graber);
            executor.add_node(pub_data);
            executor.spin();
        } catch (const std::exception& e) {
            std::cerr << "ROS2 spin error: " << e.what() << std::endl;
        }
    });

    setup();

    while (rclcpp::ok()) {
        loop();
    }

    std::cout << "Shutting down flight controller..." << std::endl;

    ros2_data_graber.reset();

    rclcpp::shutdown();

    if (ros2_thread.joinable()) {
        ros2_thread.join();
    }

    std::cout << "Flight controller shutdown complete." << std::endl;
    return 0;
}
