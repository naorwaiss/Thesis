#ifndef VAR_TYPE_HPP_
#define VAR_TYPE_HPP_

#include <eigen3/Eigen/Dense>
#include <array>

#define map_range(x, in_min, in_max, out_min, out_max) ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
#define constrain(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

#define PI 3.14159265358979323846
#define rad2deg 180.0f / PI
#define deg2rad PI / 180.0f
#define MIN_PWM 0
#define MAX_PWM 1000


struct imu_data {
    Eigen::Vector3d accel;
    Eigen::Vector3d gyro;
};

struct euler_angles {
    float roll;
    float pitch;
    float yaw;
    
    // Arithmetic operators
    euler_angles operator+(const euler_angles& other) const {
        return {roll + other.roll, pitch + other.pitch, yaw + other.yaw};
    }
    
    euler_angles operator-(const euler_angles& other) const {
        return {roll - other.roll, pitch - other.pitch, yaw - other.yaw};
    }
    
    euler_angles operator*(float scalar) const {
        return {roll * scalar, pitch * scalar, yaw * scalar};
    }
};

struct joy_data {
    float roll;
    float pitch;
    float yaw;
    float thrust;
    int aux_1_arm;
    int mode;
    int aux_3;
    int aux_4;
};

struct motor_data {
    float front_left;
    float front_right;
    float rear_left;
    float rear_right;
};

enum class drone_mod {
    rate_mode = 1,
};

struct pid_const {
    std::array<float, 5> rate_roll = {0.4f, 0.0f, 0.0f, 0.95f, 100.0f};   // P, I, D, D_filter, I_limit
    std::array<float, 5> rate_pitch = {0.4f, 0.0f, 0.0f, 0.95f, 100.0f};  // P, I, D, D_filter, I_limit
    std::array<float, 5> rate_yaw = {0.8f, 0.0f, 0.0f, 0.95f, 100.0f};    // P, I, D, D_filter, I_limit
};


struct PID_out_t {
    euler_angles error = {0.0, 0.0, 0.0};
    euler_angles P_term;
    euler_angles I_term;
    euler_angles D_term;
    euler_angles PID_return;
    euler_angles prev_err = {0.0, 0.0, 0.0};
    euler_angles prev_errHPF = {0.0, 0.0, 0.0};
    euler_angles prev_errLPF = {0.0, 0.0, 0.0};
    euler_angles prev_Iterm = {0.0, 0.0, 0.0};
    euler_angles prev_Dterm = {0.0, 0.0, 0.0};
};




#endif
