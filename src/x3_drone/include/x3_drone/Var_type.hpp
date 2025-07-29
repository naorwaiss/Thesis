#ifndef VAR_TYPE_HPP_
#define VAR_TYPE_HPP_

#include <eigen3/Eigen/Dense>


struct imu_data{
    Eigen::Vector3d accel;
    Eigen::Vector3d gyro;
};

struct euler_angles{
    float roll;
    float pitch;
    float yaw;
};


struct joy_data{
    float roll;
    float pitch;
    float yaw;
    float thrust;
    int aux_1_arm;
    int mode;
    int aux_3;
    int aux_4;
};

struct motor_data{
    float motor_A;
    float motor_B;
    float motor_C;
    float motor_D;
    float motor_E;
    float motor_F;  
    float motor_G;
    float motor_H;
};


enum class drone_mod{
    rate_mode = 1,
};







#endif
