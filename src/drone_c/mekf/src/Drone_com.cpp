#include "Drone_com.h"
#include <Arduino.h>
#include "Var_types.h"
#include "RTCom/RTCom.h"

namespace DRON_COM {
RTCom rtcomSocket(SOCKET_ADDRESS, SOCKET_CONFIG);
RTComSession* socketSession = nullptr;

float* imu_data_raw = (float*)calloc(6, sizeof(float));
uint8_t imu_byte_raw[sizeof(float) * 6];
float* imu_data_filter = (float*)calloc(12, sizeof(float));
uint8_t imu_byte_filter[sizeof(float) * 12];
float* mag_data = (float*)calloc(3, sizeof(float));
uint8_t mag_byte[sizeof(float) * 3];
float* euler_data = (float*)calloc(3, sizeof(float));
uint8_t euler_byte[sizeof(float) * 3];
float* quaternion_data = (float*)calloc(4, sizeof(float));
uint8_t quaternion_byte[sizeof(float) * 4];
int* rc_ch_data = (int*)calloc(8, sizeof(int));
uint8_t rc_byte[sizeof(int) * 8];
float* desired_rate_data = (float*)calloc(3, sizeof(float));
uint8_t desired_rate_byte[sizeof(float) * 3];
float* desired_attitud_data = (float*)calloc(3, sizeof(float));
uint8_t desired_attitud_byte[sizeof(float) * 3];
float* estimated_attitude_data = (float*)calloc(3, sizeof(float));
uint8_t estimated_attitude_byte[sizeof(float) * 3];
float* estimated_rate_data = (float*)calloc(3, sizeof(float));
uint8_t estimated_rate_byte[sizeof(float) * 3];
float* PID_stab_out_data = (float*)calloc(15, sizeof(float));
uint8_t PID_stab_out_byte[sizeof(float) * 15];
float* PID_rate_data = (float*)calloc(15, sizeof(float));
uint8_t PID_rate_byte[sizeof(float) * 15];
float* motor_data = (float*)calloc(4, sizeof(float));
uint8_t motor_pwm_byte[sizeof(float) * 4];

void onConnection(RTComSession& session) {
    Serial.printf("Session created with %s\r\n", session.address.toString());
    socketSession = &session;
    Serial.print("connect");

    session.onReceive([](const uint8_t* bytes, size_t size) {
        char data[size + 1] = {0};
        memcpy(data, bytes, size);
        Serial.println(data);
    });
}

void init_com() {
    DRON_COM::rtcomSocket.begin();
    DRON_COM::rtcomSocket.onConnection(onConnection);
}

void convert_Measurment_to_byte(Measurement_t meas,
                                quat_t q_est, attitude_t desired_attitude,
                                motor_t motor_pwm, attitude_t desired_rate,
                                attitude_t estimated_attitude, attitude_t estimated_rate,
                                PID_out_t PID_stab_out, PID_out_t PID_rate_out, Controller_s controller_data) {
    imu_data_raw[0] = meas.acc.x;
    imu_data_raw[1] = meas.acc.y;
    imu_data_raw[2] = meas.acc.z;
    imu_data_raw[3] = meas.gyroDEG.x;
    imu_data_raw[4] = meas.gyroDEG.y;
    imu_data_raw[5] = meas.gyroDEG.z;
    memcpy(imu_byte_raw, imu_data_raw, sizeof(imu_byte_raw));

    mag_data[0] = meas.mag.x;
    mag_data[1] = meas.mag.y;
    mag_data[2] = meas.mag.z;
    memcpy(mag_byte, mag_data, sizeof(mag_byte));

    imu_data_filter[0] = meas.acc_LPF.x;
    imu_data_filter[1] = meas.acc_LPF.y;
    imu_data_filter[2] = meas.acc_LPF.z;
    imu_data_filter[3] = meas.gyro_HPF.x;
    imu_data_filter[4] = meas.gyro_HPF.y;
    imu_data_filter[5] = meas.gyro_HPF.z;
    imu_data_filter[6] = meas.gyro_LPF.x;
    imu_data_filter[7] = meas.gyro_LPF.y;
    imu_data_filter[8] = meas.gyro_LPF.z;
    imu_data_filter[8] = meas.mag_LPF.x;
    imu_data_filter[9] = meas.mag_LPF.y;
    imu_data_filter[10] = meas.mag_LPF.z;
    memcpy(imu_byte_filter, imu_data_filter, sizeof(imu_byte_filter));

    quaternion_data[0] = q_est.w;
    quaternion_data[1] = q_est.x;
    quaternion_data[2] = q_est.y;
    quaternion_data[3] = q_est.z;
    memcpy(quaternion_byte, quaternion_data, sizeof(quaternion_byte));

    desired_attitud_data[0] = desired_attitude.pitch;
    desired_attitud_data[1] = desired_attitude.roll;
    desired_attitud_data[2] = desired_attitude.yaw;
    memcpy(desired_attitud_byte, desired_attitud_data, sizeof(desired_attitud_byte));

    euler_data[0] = estimated_attitude.pitch;
    euler_data[1] = estimated_attitude.roll;
    euler_data[2] = estimated_attitude.yaw;
    memcpy(euler_byte, euler_data, sizeof(euler_byte));

    desired_rate_data[0] = desired_rate.pitch;
    desired_rate_data[1] = desired_rate.roll;
    desired_rate_data[2] = desired_rate.yaw;
    memcpy(desired_rate_byte, desired_rate_data, sizeof(desired_rate_byte));

    estimated_rate_data[0] = estimated_rate.pitch;
    estimated_rate_data[1] = estimated_rate.roll;
    estimated_rate_data[2] = estimated_rate.yaw;
    memcpy(estimated_rate_byte, estimated_rate_data, sizeof(estimated_rate_byte));



    PID_stab_out_data[0] = PID_stab_out.error.pitch;
    PID_stab_out_data[1] = PID_stab_out.error.roll;
    PID_stab_out_data[2] = PID_stab_out.error.yaw;
    PID_stab_out_data[3] = PID_stab_out.P_term.pitch;
    PID_stab_out_data[4] = PID_stab_out.P_term.roll;
    PID_stab_out_data[5] = PID_stab_out.P_term.yaw;
    PID_stab_out_data[6] = PID_stab_out.I_term.pitch;
    PID_stab_out_data[7] = PID_stab_out.I_term.roll;
    PID_stab_out_data[8] = PID_stab_out.I_term.yaw;
    PID_stab_out_data[9] = PID_stab_out.D_term.pitch;
    PID_stab_out_data[10] = PID_stab_out.D_term.roll;
    PID_stab_out_data[11] = PID_stab_out.D_term.yaw;
    PID_stab_out_data[12] = PID_stab_out.PID_ret.pitch;
    PID_stab_out_data[13] = PID_stab_out.PID_ret.roll;
    PID_stab_out_data[14] = PID_stab_out.PID_ret.yaw;
    memcpy(PID_stab_out_byte, PID_stab_out_data, sizeof(PID_stab_out_byte));

    PID_rate_data[0] = PID_rate_out.error.pitch;
    PID_rate_data[1] = PID_rate_out.error.roll;
    PID_rate_data[2] = PID_rate_out.error.yaw;
    PID_rate_data[3] = PID_rate_out.P_term.pitch;
    PID_rate_data[4] = PID_rate_out.P_term.roll;
    PID_rate_data[5] = PID_rate_out.P_term.yaw;
    PID_rate_data[6] = PID_rate_out.I_term.pitch;
    PID_rate_data[7] = PID_rate_out.I_term.roll;
    PID_rate_data[8] = PID_rate_out.I_term.yaw;
    PID_rate_data[9] = PID_rate_out.D_term.pitch;
    PID_rate_data[10] = PID_rate_out.D_term.roll;
    PID_rate_data[11] = PID_rate_out.D_term.yaw;
    PID_rate_data[12] = PID_rate_out.PID_ret.pitch;
    PID_rate_data[13] = PID_rate_out.PID_ret.roll;
    PID_rate_data[14] = PID_rate_out.PID_ret.yaw;
    memcpy(PID_rate_byte, PID_rate_data, sizeof(PID_rate_byte));

    motor_data[0] = motor_pwm.PWM1;
    motor_data[1] = motor_pwm.PWM2;
    motor_data[2] = motor_pwm.PWM3;
    motor_data[3] = motor_pwm.PWM4;
    // for (size_t i = 0; i < 4; i++) {
    //     motor_data[i] = map(motor_data[i], 2200, 4000, 0, 100);
    // }
    memcpy(motor_pwm_byte, motor_data, sizeof(motor_pwm_byte));

    rc_ch_data[0] = controller_data.roll;
    rc_ch_data[1] = controller_data.pitch;
    rc_ch_data[2] = controller_data.throttle;
    rc_ch_data[3] = controller_data.yaw;
    rc_ch_data[4] = controller_data.aux1;
    rc_ch_data[5] = controller_data.aux2;
    rc_ch_data[6] = controller_data.aux3;
    rc_ch_data[7] = controller_data.aux4;
    memcpy(rc_byte, rc_ch_data, sizeof(rc_byte));
}

void emit_data() {
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
}

void send_data() {
    DRON_COM::rtcomSocket.process();
    if (rtcomSocket.isSessionConnected(socketSession)) {
        DRON_COM::emit_data();
    };
}

}  // namespace DRON_COM