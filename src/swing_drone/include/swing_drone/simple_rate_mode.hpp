#ifndef SIMPLE_RATE_MODE_HPP
#define SIMPLE_RATE_MODE_HPP

#include "Var_type.hpp"
#include "Eigen/Dense"
#include "Eigen/Core"
#include "Eigen/Geometry"
#include "swing_drone/pub.hpp"

class simple_rate_mode{
    public:
        simple_rate_mode(pub* pub_ptr, imu_data* imu_read, joy_data* joy_read , float DT_hz);
        void run_rate_mode();

    private:
        void angle_constrain();
        void PID_operation();
        void Motor_Mix();
        void run_rate_loop();
        
        imu_data* _imu_read;
        joy_data* _joy_read;
        float _DT_SEC;
        pub* _pub_ptr;
        PID_out_t _pid_rate;
        euler_angles _actual_rate;
        euler_angles _des_rate;
        float _throttle_modifier;
        
        // Missing variables used in implementation
        float _rate_angle_limit = 200.0f;
        PID_out_t PID_rate;
        motor_data _Motor_struct;
        
        // PID constants structure (needs to be defined)
        struct {
            float rate_roll[3] = {0.9f, 0.05f, 0.0f};    // P, I, D, 
            float rate_pitch[3] = {0.9f, 0.05f, 0.0f};   // P, I, D,  
            float rate_yaw[3] = {0.9f, 0.0f, 0.0f};     // P, I, D,
        } _pid_const;

};





#endif
