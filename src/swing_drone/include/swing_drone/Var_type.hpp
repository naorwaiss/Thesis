#ifndef VAR_TYPE_HPP_
#define VAR_TYPE_HPP_

#include <eigen3/Eigen/Dense>

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

    // Default constructor
    euler_angles() = default;
    
    // Constructor with three parameters
    euler_angles(float r, float p, float y) : roll(r), pitch(p), yaw(y) {}
    
    // Copy constructor
    euler_angles(const euler_angles& other) 
        : roll(other.roll), pitch(other.pitch), yaw(other.yaw) {}

    // Operator overloads for PID calculations
    euler_angles operator-(const euler_angles& other) const {
        return euler_angles(roll - other.roll, pitch - other.pitch, yaw - other.yaw);
    }

    euler_angles operator+(const euler_angles& other) const {
        return euler_angles(roll + other.roll, pitch + other.pitch, yaw + other.yaw);
    }

    euler_angles operator*(float scalar) const {
        return euler_angles(roll * scalar, pitch * scalar, yaw * scalar);
    }

    euler_angles& operator=(const euler_angles& other) {
        roll = other.roll;
        pitch = other.pitch;
        yaw = other.yaw;
        return *this;
    }
};

struct arm_data {
    Eigen::Vector4d encoder_position;
    Eigen::Vector4d encoder_velocity;
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
    float motor_A;
    float motor_B;
    float motor_C;
    float motor_D;
    float motor_E;
    float motor_F;
    float motor_G;
    float motor_H;
};

enum class drone_mod {
    backstepping = 0,
    rate_mode = 1,
    
};

enum class arm_statuse {
    dis_arm = 0,
    arm = 1,
};

struct PID_out_t {
    euler_angles error = euler_angles(0.0, 0.0, 0.0);
    euler_angles P_term = euler_angles(0.0, 0.0, 0.0);
    euler_angles I_term = euler_angles(0.0, 0.0, 0.0);
    euler_angles D_term = euler_angles(0.0, 0.0, 0.0);
    euler_angles PID_return = euler_angles(0.0, 0.0, 0.0);
    euler_angles prev_err = euler_angles(0.0, 0.0, 0.0);
    euler_angles prev_Iterm = euler_angles(0.0, 0.0, 0.0);
    euler_angles prev_Dterm = euler_angles(0.0, 0.0, 0.0);
};

#endif
