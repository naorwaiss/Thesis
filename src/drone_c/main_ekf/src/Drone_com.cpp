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
uint8_t imu_byte_filter[sizeof(float)*12];
float* mag_data = (float*)calloc(3, sizeof(float));
uint8_t mag_byte[sizeof(float) * 3];
float* euler_data = (float*)calloc(3, sizeof(float));
uint8_t euler_byte[sizeof(float) * 3];
float* quaternion_data = (float*)calloc(4, sizeof(float));
uint8_t quaternion_byte[sizeof(float) * 4];

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
                             quat_t q_est, attitude_t estimated_attitude){
    imu_data_raw[0] = meas.acc.x;
    imu_data_raw[1] = meas.acc.y;
    imu_data_raw[2] = meas.acc.z;
    imu_data_raw[3] = meas.gyro.x;
    imu_data_raw[4] = meas.gyro.y;
    imu_data_raw[5] = meas.gyro.z;
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

    euler_data[0] = estimated_attitude.pitch;
    euler_data[1] = estimated_attitude.roll;
    euler_data[2] = estimated_attitude.yaw;
    memcpy(euler_byte, euler_data, sizeof(euler_byte));


}

void emit_data() {
    socketSession->emitTyped(imu_byte_raw, sizeof(imu_byte_raw), P_IMU_RAW);
    socketSession->emitTyped(imu_byte_filter, sizeof(imu_byte_filter), P_IMU_FILTER);
    socketSession->emitTyped(mag_byte, sizeof(mag_byte), MAG);
    socketSession->emitTyped(quaternion_byte, sizeof(quaternion_byte), Quaternion);
    socketSession->emitTyped(euler_byte, sizeof(euler_byte), EUILER);
}

void send_data() {
    rtcomSocket.process();
    if (rtcomSocket.isSessionConnected(socketSession)) {
        DRON_COM::emit_data();
    };
}

}  // namespace DR