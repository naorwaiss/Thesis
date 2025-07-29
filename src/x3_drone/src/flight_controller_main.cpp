#include <iostream>
#include <chrono>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "x3_drone/Var_type.hpp"
#include "x3_drone/ros2_data_graber.hpp"
#include "x3_drone/micros_lib.hpp"
// Global variables - Arduino style
bool system_initialized = false;
const int LOOP_FREQUENCY_HZ = 50;  // Set desired loop frequency here
const auto LOOP_PERIOD_MICROS = std::chrono::microseconds(1000000 / LOOP_FREQUENCY_HZ);

// Global sensor data - automatically updated by ROS2
imu_data imu_data_read;
euler_angles euler_angles_read;
joy_data joy_data_read;


// ROS2 node for data collection (runs in background)
std::shared_ptr<data_graber_ros> data_graber;
std::thread ros2_thread;

elapsed_timer loop_timer(LOOP_FREQUENCY_HZ);

// Declare a pub object
void setup() {
    std::cout << "Flight Controller Setup..." << std::endl;
    system_initialized = true;
    std::cout << "Flight Controller Setup Complete!" << std::endl;
    std::cout << "Running main loop at " << LOOP_FREQUENCY_HZ << " Hz" << std::endl;
}

// Arduino-like loop function
void loop() {
    
    // if (!system_initialized) return;

    if (loop_timer.has_elapsed()) {
        printf("Rate mode\n");
        loop_timer.reset();

    }
    // else{
    //     printf("Waiting for data...\n");
    // }
}





int main(int argc, char** argv) {
    // Initialize ROS2 (hidden from Arduino-like code)
    rclcpp::init(argc, argv);

    // Create ROS2 data grabber node
    data_graber = std::make_shared<data_graber_ros>(&imu_data_read, &euler_angles_read, &joy_data_read);

    // Start ROS2 in background thread (like Arduino's background processes)
    ros2_thread = std::thread([]() {
        try {
            rclcpp::spin(data_graber);
        } catch (const std::exception& e) {
            std::cerr << "ROS2 spin error: " << e.what() << std::endl;
        }
    });

    setup();

    while (rclcpp::ok()) {
        loop();
    }

    // Cleanup - properly shutdown ROS2 first
    std::cout << "Shutting down flight controller..." << std::endl;

    // Reset the shared pointer to trigger proper destruction
    data_graber.reset();

    // Shutdown ROS2
    rclcpp::shutdown();

    // Wait for ROS2 thread to finish
    if (ros2_thread.joinable()) {
        ros2_thread.join();
    }

    std::cout << "Flight controller shutdown complete." << std::endl;
    return 0;
}
