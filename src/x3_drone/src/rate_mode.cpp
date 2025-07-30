#include "x3_drone/rate_mode.hpp"


rate_mode::rate_mode(pub* pub_ptr, imu_data* imu_data_ptr, euler_angles* euler_angles_ptr, joy_data* joy_data_ptr , float DT_hz)
{
    _imu_data = imu_data_ptr;
    _euler_angles = euler_angles_ptr;
    _joy_data = joy_data_ptr;
    _DT_SEC = 1.0f / DT_hz;
    _pub_ptr = pub_ptr;
}

rate_mode::~rate_mode()
{
    // Destructor implementation - nothing special needed for cleanup
}


void rate_mode::angle_constrain() { 
    _des_rate.roll = map_range(_joy_data->roll, -1.0f, 1.0f, -_rate_angle_limit, _rate_angle_limit);
    _des_rate.pitch = map_range(_joy_data->pitch, -1.0f, 1.0f, -_rate_angle_limit, _rate_angle_limit);
    _des_rate.yaw = map_range(_joy_data->yaw, -1.0f, 1.0f, -_rate_angle_limit, _rate_angle_limit);
    _pub_ptr->publish_dis_rate(_des_rate);
    _pub_ptr->publish_actual_rate(_actual_rate);
    _throttle_modifier = map_range(_joy_data->thrust, -1.0f, 1.0f, MIN_PWM, MAX_PWM);
}

void rate_mode::PID_operation() {  // Actual rate will be in deg/s

    // Calculate error
    PID_rate.error = _des_rate - _actual_rate;  // Probably the best for the Proportional term?

    // Calculate P term:
    PID_rate.P_term.roll = _pid_const.rate_roll[0] * PID_rate.error.roll;
    PID_rate.P_term.pitch = _pid_const.rate_pitch[0] * PID_rate.error.pitch;
    PID_rate.P_term.yaw = _pid_const.rate_yaw[0] * PID_rate.error.yaw;

    // Calculate I term:
    PID_rate.I_term.roll = PID_rate.prev_Iterm.roll + (_pid_const.rate_roll[1] / 2) * (PID_rate.error.roll + PID_rate.prev_err.roll) * _DT_SEC;
    PID_rate.I_term.pitch = PID_rate.prev_Iterm.pitch + (_pid_const.rate_pitch[1] / 2) * (PID_rate.error.pitch + PID_rate.prev_err.pitch) * _DT_SEC;
    PID_rate.I_term.yaw = PID_rate.prev_Iterm.yaw + (_pid_const.rate_yaw[1] / 2) * (PID_rate.error.yaw + PID_rate.prev_err.yaw) * _DT_SEC;

    // Apply HPF to the derivative term
    PID_rate.D_term.roll = _pid_const.rate_roll[2] * _pid_const.rate_roll[3] * (PID_rate.error.roll - PID_rate.prev_err.roll + PID_rate.D_term.roll);
    PID_rate.D_term.pitch = _pid_const.rate_pitch[2] * _pid_const.rate_pitch[3] * (PID_rate.error.pitch - PID_rate.prev_err.pitch + PID_rate.D_term.pitch);
    PID_rate.D_term.yaw = _pid_const.rate_yaw[2] * _pid_const.rate_yaw[3] * (PID_rate.error.yaw - PID_rate.prev_err.yaw + PID_rate.D_term.yaw);

    // Cap the I term
    PID_rate.I_term.roll = constrain(PID_rate.I_term.roll, -_pid_const.rate_roll[4], _pid_const.rate_roll[4]);
    PID_rate.I_term.pitch = constrain(PID_rate.I_term.pitch, -_pid_const.rate_pitch[4], _pid_const.rate_pitch[4]);
    PID_rate.I_term.yaw = constrain(PID_rate.I_term.yaw, -_pid_const.rate_yaw[4], _pid_const.rate_yaw[4]);

    // Time propagation for relevant variables:
    PID_rate.prev_err = PID_rate.error;
    PID_rate.prev_Iterm = PID_rate.I_term;
    // Return the output
    PID_rate.PID_return = PID_rate.P_term + PID_rate.I_term + PID_rate.D_term;
    _pub_ptr->pid_value_publish(PID_rate);
}


void rate_mode::Motor_Mix() {
    _Motor_struct.front_left = _throttle_modifier - PID_rate.PID_return.roll - PID_rate.PID_return.pitch - PID_rate.PID_return.yaw;
    _Motor_struct.front_right = _throttle_modifier - PID_rate.PID_return.roll + PID_rate.PID_return.pitch + PID_rate.PID_return.yaw;
    _Motor_struct.rear_left = _throttle_modifier + PID_rate.PID_return.roll + PID_rate.PID_return.pitch - PID_rate.PID_return.yaw;
    _Motor_struct.rear_right = _throttle_modifier + PID_rate.PID_return.roll - PID_rate.PID_return.pitch + PID_rate.PID_return.yaw;
 
    // Constrain the values to be between 0 and 1000
    _Motor_struct.front_left = constrain(_Motor_struct.front_left, MIN_PWM, MAX_PWM);
    _Motor_struct.front_right = constrain(_Motor_struct.front_right, MIN_PWM, MAX_PWM);
    _Motor_struct.rear_left = constrain(_Motor_struct.rear_left, MIN_PWM, MAX_PWM);
    _Motor_struct.rear_right = constrain(_Motor_struct.rear_right, MIN_PWM, MAX_PWM);


    _pub_ptr->publish_motor_data(_Motor_struct);

}


void rate_mode::run_rate_mode() {
    angle_constrain();
    PID_operation();
    Motor_Mix();
}


