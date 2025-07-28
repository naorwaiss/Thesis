#ifndef SIMPLE_RATE_MODE_HPP
#define SIMPLE_RATE_MODE_HPP

#include "Var_type.hpp"
#include "Eigen/Dense"
#include "Eigen/Core"
#include "Eigen/Geometry"


class simple_rate_mode{
    public:
        simple_rate_mode(imu_data* imu_read);
        ~simple_rate_mode();
        void rate_mode_control();
        void pid_control();
        void motor_mixing();

    private:
        imu_data _imu_read;
        euler_angles _euler_angles_read;
        
};





#endif
