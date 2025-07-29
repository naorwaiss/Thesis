#ifndef RATE_MODE_HPP
#define RATE_MODE_HPP

#include "Var_type.hpp"


class rate_mode {
    public:
        rate_mode(imu_data* imu_data_ptr, euler_angles* euler_angles_ptr, joy_data* joy_data_ptr, float DT_hz);
        ~rate_mode();
        void rate_run();
        void PID_operation();
        void run_rate_mode();
    private:
        float _DT_SEC;
        void angle_constrain();
        PID_out_t PID_rate;
        imu_data* _imu_data;
        euler_angles* _euler_angles;
        joy_data* _joy_data;
        pid_const _pid_const;
        euler_angles _des_rate;
        euler_angles _actual_rate;
        angle_limit _angle_limit;



};








#endif
