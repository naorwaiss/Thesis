#ifndef RATE_MODE_HPP
#define RATE_MODE_HPP

#include "Var_type.hpp"
#include "x3_drone/pub.hpp"

class rate_mode {
    public:
        rate_mode(pub* pub_ptr, imu_data* imu_data_ptr, euler_angles* euler_angles_ptr, joy_data* joy_data_ptr, float DT_hz);
        ~rate_mode();
        void PID_operation();
        void run_rate_mode();
        void Motor_Mix();
        euler_angles _des_rate;
        euler_angles _actual_rate;
        

    private:
        float _DT_SEC;
        void angle_constrain();
        PID_out_t PID_rate;
        imu_data* _imu_data;
        euler_angles* _euler_angles;
        joy_data* _joy_data;
        pid_const _pid_const;
        pub* _pub_ptr;
        motor_data _Motor_struct;
        int _rate_angle_limit = 200;
        float _throttle_modifier;
};


#endif
