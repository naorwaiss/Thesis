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


enum class drone_mod{
    backstepping = 0,
    rate_mode = 1,
};




#endif
