#include "drone_comclass.h"
#include <Arduino.h>

// Define static member variables
RTComSession* Drone_com::socketSession = nullptr;
Measurement_t* Drone_com::_meas = nullptr;
quat_t* Drone_com::_q_est = nullptr;
attitude_t* Drone_com::_desired_attitude = nullptr;
motor_t* Drone_com::_motor_pwm = nullptr;  // Currently not in use. replaced by PID_rate_out.PID_ret
attitude_t* Drone_com::_desired_rate = nullptr;
attitude_t* Drone_com::_estimated_attitude = nullptr;
attitude_t* Drone_com::_estimated_rate = nullptr;
PID_out_t* Drone_com::_PID_stab_out = nullptr;
PID_out_t* Drone_com::_PID_rate_out = nullptr;
Controller_s* Drone_com::_controller_data = nullptr;
drone_tune_t* Drone_com::_drone_tune = nullptr;
Drone_Data_t* Drone_com::_drone_data_header = nullptr;
CompFilter* Drone_com::_comfilter = nullptr;

void Drone_com::onConnection(RTComSession& session) {
    Serial.printf("Session created with %s\r\n", session.address.toString());
    socketSession = &session;
    Serial.print("connect");

    session.on(PID_CONSTS_RETURN, [](const uint8_t* bytes, size_t size) {
        if (socketSession == nullptr || size != sizeof(float) * 15) {
            Serial.print("problem at the pid arraive");
        } else {
            float* pid_const_Data_arrive = (float*)calloc(15, sizeof(float));
            memcpy(pid_const_Data_arrive, bytes, sizeof(float) * 15);
            PID_const_t new_pid_const;
            new_pid_const.defaultRpitchPID = {pid_const_Data_arrive[0], pid_const_Data_arrive[1], pid_const_Data_arrive[2]};
            new_pid_const.defaultRrollPID = {pid_const_Data_arrive[3], pid_const_Data_arrive[4], pid_const_Data_arrive[5]};
            new_pid_const.defaultRyawPID = {pid_const_Data_arrive[6], pid_const_Data_arrive[7], pid_const_Data_arrive[8]};
            new_pid_const.defaultSrollPID = {pid_const_Data_arrive[9], pid_const_Data_arrive[10], pid_const_Data_arrive[11]};
            new_pid_const.defaultSpitchPID = {pid_const_Data_arrive[12], pid_const_Data_arrive[13], pid_const_Data_arrive[14]};
            new_pid_const.defaultSyawPID = {0, 0, 0};
            new_pid_const.defaultImax_rate = {40, 40};
            new_pid_const.defaultImax_stab = {40, 40};
            setPID_params(&new_pid_const);
        }
    });
    session.on(FILTER_CONSTS_RETURN, [](const uint8_t* bytes, size_t size) {
        if (socketSession == nullptr || size != sizeof(float) * 3) {
            Serial.print("problem at the pid arraive");
        } else {
            float* filter_const_Data_arrive = (float*)calloc(3, sizeof(float));
            memcpy(filter_const_Data_arrive, bytes, sizeof(float) * 3);
            magwick_data_t new_magwick_data;
            new_magwick_data.std_beta = filter_const_Data_arrive[0];
            new_magwick_data.high_beta = filter_const_Data_arrive[1];
            new_magwick_data.low_beta = filter_const_Data_arrive[2];
            if (_comfilter != nullptr) {
                _comfilter->set_beta(&new_magwick_data);
            }

        }
    });
}

Drone_com::Drone_com(Measurement_t* meas, quat_t* q_est, attitude_t* desired_attitude, motor_t* motor_pwm,
                     attitude_t* desired_rate, attitude_t* estimated_attitude, attitude_t* estimated_rate,
                     PID_out_t* PID_stab_out, PID_out_t* PID_rate_out, Controller_s* controller_data,
                     drone_tune_t* drone_tune, Drone_Data_t* drone_data_header, CompFilter* comfilter)
    : rtcomSocket(SOCKET_ADDRESS, SOCKET_CONFIG)  // Initialize rtcomSocket with both address and config
{
    _meas = meas;
    _q_est = q_est;
    _desired_attitude = desired_attitude;
    _motor_pwm = motor_pwm;
    _desired_rate = desired_rate;
    _estimated_attitude = estimated_attitude;
    _estimated_rate = estimated_rate;
    _PID_stab_out = PID_stab_out;
    _PID_rate_out = PID_rate_out;
    _controller_data = controller_data;
    _drone_tune = drone_tune;  // Store the pointer instead of making a copy
    _drone_data_header = drone_data_header;
    _comfilter = comfilter;
}

void Drone_com::init_com() {
    rtcomSocket.begin();
    rtcomSocket.onConnection(onConnection);
}

void Drone_com::convert_Measurment_to_byte() {
    imu_data_raw[0] = _meas->acc.x;
    imu_data_raw[1] = _meas->acc.y;
    imu_data_raw[2] = _meas->acc.z;
    imu_data_raw[3] = _meas->gyroDEG.x;
    imu_data_raw[4] = _meas->gyroDEG.y;
    imu_data_raw[5] = _meas->gyroDEG.z;
    memcpy(imu_byte_raw, imu_data_raw, sizeof(imu_byte_raw));

    mag_data[0] = _meas->mag.x;
    mag_data[1] = _meas->mag.y;
    mag_data[2] = _meas->mag.z;
    memcpy(mag_byte, mag_data, sizeof(mag_byte));

    imu_data_filter[0] = _meas->acc_LPF.x;
    imu_data_filter[1] = _meas->acc_LPF.y;
    imu_data_filter[2] = _meas->acc_LPF.z;
    imu_data_filter[3] = _meas->gyro_HPF.x;
    imu_data_filter[4] = _meas->gyro_HPF.y;
    imu_data_filter[5] = _meas->gyro_HPF.z;
    imu_data_filter[6] = _meas->gyro_LPF.x;
    imu_data_filter[7] = _meas->gyro_LPF.y;
    imu_data_filter[8] = _meas->gyro_LPF.z;
    imu_data_filter[9] = _meas->mag_LPF.x;
    imu_data_filter[10] = _meas->mag_LPF.y;
    imu_data_filter[11] = _meas->mag_LPF.z;
    memcpy(imu_byte_filter, imu_data_filter, sizeof(imu_byte_filter));

    quaternion_data[0] = _q_est->w;
    quaternion_data[1] = _q_est->x;
    quaternion_data[2] = _q_est->y;
    quaternion_data[3] = _q_est->z;
    memcpy(quaternion_byte, quaternion_data, sizeof(quaternion_byte));

    desired_attitud_data[0] = _desired_attitude->pitch;
    desired_attitud_data[1] = _desired_attitude->roll;
    desired_attitud_data[2] = _desired_attitude->yaw;
    memcpy(desired_attitud_byte, desired_attitud_data, sizeof(desired_attitud_byte));

    euler_data[0] = _estimated_attitude->pitch;
    euler_data[1] = _estimated_attitude->roll;
    euler_data[2] = _estimated_attitude->yaw;
    memcpy(euler_byte, euler_data, sizeof(euler_byte));

    desired_rate_data[0] = _desired_rate->pitch;
    desired_rate_data[1] = _desired_rate->roll;
    desired_rate_data[2] = _desired_rate->yaw;
    memcpy(desired_rate_byte, desired_rate_data, sizeof(desired_rate_byte));

    estimated_rate_data[0] = _estimated_rate->pitch;
    estimated_rate_data[1] = _estimated_rate->roll;
    estimated_rate_data[2] = _estimated_rate->yaw;
    memcpy(estimated_rate_byte, estimated_rate_data, sizeof(estimated_rate_byte));

    PID_stab_out_data[0] = _PID_stab_out->error.pitch;
    PID_stab_out_data[1] = _PID_stab_out->error.roll;
    PID_stab_out_data[2] = _PID_stab_out->error.yaw;
    PID_stab_out_data[3] = _PID_stab_out->P_term.pitch;
    PID_stab_out_data[4] = _PID_stab_out->P_term.roll;
    PID_stab_out_data[5] = _PID_stab_out->P_term.yaw;
    PID_stab_out_data[6] = _PID_stab_out->I_term.pitch;
    PID_stab_out_data[7] = _PID_stab_out->I_term.roll;
    PID_stab_out_data[8] = _PID_stab_out->I_term.yaw;
    PID_stab_out_data[9] = _PID_stab_out->D_term.pitch;
    PID_stab_out_data[10] = _PID_stab_out->D_term.roll;
    PID_stab_out_data[11] = _PID_stab_out->D_term.yaw;
    PID_stab_out_data[12] = _PID_stab_out->PID_ret.pitch;
    PID_stab_out_data[13] = _PID_stab_out->PID_ret.roll;
    PID_stab_out_data[14] = _PID_stab_out->PID_ret.yaw;
    memcpy(PID_stab_out_byte, PID_stab_out_data, sizeof(PID_stab_out_byte));

    PID_rate_data[0] = _PID_rate_out->error.pitch;
    PID_rate_data[1] = _PID_rate_out->error.roll;
    PID_rate_data[2] = _PID_rate_out->error.yaw;
    PID_rate_data[3] = _PID_rate_out->P_term.pitch;
    PID_rate_data[4] = _PID_rate_out->P_term.roll;
    PID_rate_data[5] = _PID_rate_out->P_term.yaw;
    PID_rate_data[6] = _PID_rate_out->I_term.pitch;
    PID_rate_data[7] = _PID_rate_out->I_term.roll;
    PID_rate_data[8] = _PID_rate_out->I_term.yaw;
    PID_rate_data[9] = _PID_rate_out->D_term.pitch;
    PID_rate_data[10] = _PID_rate_out->D_term.roll;
    PID_rate_data[11] = _PID_rate_out->D_term.yaw;
    PID_rate_data[12] = _PID_rate_out->PID_ret.pitch;
    PID_rate_data[13] = _PID_rate_out->PID_ret.roll;
    PID_rate_data[14] = _PID_rate_out->PID_ret.yaw;
    memcpy(PID_rate_byte, PID_rate_data, sizeof(PID_rate_byte));

    motor_data[0] = _motor_pwm->PWM1;
    motor_data[1] = _motor_pwm->PWM2;
    motor_data[2] = _motor_pwm->PWM3;
    motor_data[3] = _motor_pwm->PWM4;
    memcpy(motor_pwm_byte, motor_data, sizeof(motor_pwm_byte));

    rc_ch_data[0] = _controller_data->roll;
    rc_ch_data[1] = _controller_data->pitch;
    rc_ch_data[2] = _controller_data->throttle;
    rc_ch_data[3] = _controller_data->yaw;
    rc_ch_data[4] = _controller_data->aux1;
    rc_ch_data[5] = _controller_data->aux2;
    rc_ch_data[6] = _controller_data->aux3;
    rc_ch_data[7] = _controller_data->aux4;
    memcpy(rc_byte, rc_ch_data, sizeof(rc_byte));

    pid_const_Data[0] = _drone_tune->pid_const.defaultRpitchPID[0];
    pid_const_Data[1] = _drone_tune->pid_const.defaultRpitchPID[1];
    pid_const_Data[2] = _drone_tune->pid_const.defaultRpitchPID[2];
    pid_const_Data[3] = _drone_tune->pid_const.defaultRrollPID[0];
    pid_const_Data[4] = _drone_tune->pid_const.defaultRrollPID[1];
    pid_const_Data[5] = _drone_tune->pid_const.defaultRrollPID[2];
    pid_const_Data[6] = _drone_tune->pid_const.defaultSpitchPID[0];
    pid_const_Data[7] = _drone_tune->pid_const.defaultSpitchPID[1];
    pid_const_Data[8] = _drone_tune->pid_const.defaultSpitchPID[2];
    pid_const_Data[9] = _drone_tune->pid_const.defaultSrollPID[0];
    pid_const_Data[10] = _drone_tune->pid_const.defaultSrollPID[1];
    pid_const_Data[11] = _drone_tune->pid_const.defaultSrollPID[2];
    pid_const_Data[12] = _drone_tune->pid_const.defaultRyawPID[0];
    pid_const_Data[13] = _drone_tune->pid_const.defaultRyawPID[1];
    pid_const_Data[14] = _drone_tune->pid_const.defaultRyawPID[2];
    memcpy(pid_consts_byte, pid_const_Data, sizeof(pid_consts_byte));

    for (size_t i = 0; i < 6; i++) {
        drone_header_byte[i] = _drone_data_header->mac[i];
    }
    drone_header_byte[6] = static_cast<uint8_t>(_drone_data_header->drone_mode);
    drone_header_byte[7] = static_cast<uint8_t>(_drone_data_header->filter_mode);
    drone_header_byte[8] = static_cast<uint8_t>(_drone_data_header->is_armed);
    memcpy(&drone_header_byte[9], &_drone_data_header->voltage_reading, sizeof(float));
    memcpy(&drone_header_byte[13], &_drone_data_header->current_reading, sizeof(float));

    magwick_data[0] = _drone_tune->filter_data.std_beta;
    magwick_data[1] = _drone_tune->filter_data.high_beta;
    magwick_data[2] = _drone_tune->filter_data.low_beta;
    memcpy(magwick_data_byte, magwick_data, sizeof(magwick_data_byte));
}

void Drone_com::emit_data() {
    socketSession->emitTyped(imu_byte_raw, sizeof(imu_byte_raw), P_IMU_RAW);
    socketSession->emitTyped(imu_byte_filter, sizeof(imu_byte_filter), P_IMU_FILTER);
    socketSession->emitTyped(mag_byte, sizeof(mag_byte), MAG);
    socketSession->emitTyped(quaternion_byte, sizeof(quaternion_byte), Quaternion_n);
    socketSession->emitTyped(euler_byte, sizeof(euler_byte), EUILER);
    socketSession->emitTyped(rc_byte, sizeof(rc_byte), RC);
    socketSession->emitTyped(desired_rate_byte, sizeof(desired_rate_byte), D_RATE);
    socketSession->emitTyped(desired_attitud_byte, sizeof(desired_attitud_byte), D_ATI);
    socketSession->emitTyped(estimated_rate_byte, sizeof(estimated_rate_byte), EST_RATE);
    socketSession->emitTyped(PID_stab_out_byte, sizeof(PID_stab_out_byte), PID_stab_prase);
    socketSession->emitTyped(PID_rate_byte, sizeof(PID_rate_byte), PID_rate_prase);
    socketSession->emitTyped(motor_pwm_byte, sizeof(motor_pwm_byte), MOTOR_DATA_CONST);
    socketSession->emitTyped(pid_consts_byte, sizeof(pid_consts_byte), PID_CONSTS_DATA);
    socketSession->emitTyped(drone_header_byte, sizeof(drone_header_byte), DRONE_SIGNATURE);
    socketSession->emitTyped(magwick_data_byte, sizeof(magwick_data_byte), MAGWICK_DATA);
}

void Drone_com::send_data() {
    rtcomSocket.process();
    if (rtcomSocket.isSessionConnected(socketSession)) {
        emit_data();
    };
}