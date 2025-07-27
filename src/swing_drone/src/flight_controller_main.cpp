#include <iostream>
#include <chrono>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "swing_drone/Var_type.hpp"
#include "swing_drone/ros2_data_graber.hpp"
#include "swing_drone/micros_lib.hpp"

// Global variables - Arduino style
bool system_initialized = false;
const int LOOP_FREQUENCY_HZ = 50; // Set desired loop frequency here
const auto LOOP_PERIOD_MICROS = std::chrono::microseconds(1000000 / LOOP_FREQUENCY_HZ);

// Global sensor data - automatically updated by ROS2
imu_data imu_data_read; 
euler_angles euler_angles_read;

// ROS2 node for data collection (runs in background)
std::shared_ptr<data_graber_ros> imu_data_graber;
std::thread ros2_thread;

elapsed_timer loop_timer(LOOP_FREQUENCY_HZ);

// Arduino-like setup function (replaces init)
void setup() {
    std::cout << "Flight Controller Setup..." << std::endl;
    
    // Initialize your flight controller here
    system_initialized = true;
    
    std::cout << "Flight Controller Setup Complete!" << std::endl;
    std::cout << "Running main loop at " << LOOP_FREQUENCY_HZ << " Hz" << std::endl;
}

// Arduino-like loop function
void loop() {
    if (!system_initialized) return;
    
    
    
    if (loop_timer.has_elapsed()) {
        std::cout << " - IMU Accel: [" 
                  << imu_data_read.accel.x() << ", " 
                  << imu_data_read.accel.y() << ", " 
                  << imu_data_read.accel.z() << "] "
                  << " - IMU Gyro: [" << imu_data_read.gyro.x() << ", " 
                  << imu_data_read.gyro.x() << ", " 
                  << imu_data_read.gyro.y() << ", " 
                  << imu_data_read.gyro.z() << "] "
                  << "Euler: [" << euler_angles_read.roll << ", " 
                  << euler_angles_read.pitch << ", " 
                  << euler_angles_read.yaw << "]" << std::endl;
        
        // Reset timer only AFTER printing
        loop_timer.reset();
    }
}

int main(int argc, char** argv) {
    // Initialize ROS2 (hidden from Arduino-like code)
    rclcpp::init(argc, argv);
    
    // Create ROS2 data grabber node
    imu_data_graber = std::make_shared<data_graber_ros>(&imu_data_read, &euler_angles_read);
    
    // Start ROS2 in background thread (like Arduino's background processes)
    ros2_thread = std::thread([]() {
        try {
            rclcpp::spin(imu_data_graber);
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
    imu_data_graber.reset();
    
    // Shutdown ROS2
    rclcpp::shutdown();
    
    // Wait for ROS2 thread to finish
    if (ros2_thread.joinable()) {
        ros2_thread.join();
    }
    
    std::cout << "Flight controller shutdown complete." << std::endl;
    return 0;
}
