#include "sender.h"

RTComSession* sender::socketSession = nullptr;
gnd_bot* sender::my_bot = nullptr;
roller* sender::my_roller = nullptr;
ImuMadgwick* sender::my_imu = nullptr;

sender::sender(RTComSession* session, gnd_bot* gnd_instance, roller* roller_instance,ImuMadgwick* imu_instance) {
    socketSession = session;
    my_bot = gnd_instance;      
    my_roller = roller_instance;
    my_imu = imu_instance;

}

void sender::update_session(RTComSession& newsession) {
    socketSession = &newsession;
}

void sender::convert_data() {
    float float_odom[5];
    float_odom[0] = my_bot->robot.x_estimate;
    float_odom[1] = my_bot->robot.y_estimate;
    float_odom[2] = my_bot->robot.omega_estimate;
    float_odom[3] = my_bot->robot.x_dot_estimate;
    float_odom[4] = my_bot->robot.omega_dot_estimate;
    conver_and_send_data(float_odom, sizeof(float)*5, ODOM_TYPE);
    float float_twist[2];
    float_twist[0] = my_bot->robot.omega_dot_cmmand;
    float_twist[1] = my_bot->robot.x_dot_cmmand;
    conver_and_send_data(float_twist, sizeof(float)*2, TWIST_TYPE);
    float linear_velo[2];
    linear_velo[0] = my_bot->right_motor.wheel_linera_speed;
    linear_velo[1] = my_bot->left_motor.wheel_linera_speed;
    conver_and_send_data(linear_velo, sizeof(float)*2, LINEAR_VELO);
    float roller_data[3];
    roller_data[0] = my_roller->load_cell.tension;
    roller_data[1] = my_roller->load_cell.error;
    roller_data[2] = my_roller->load_cell.dis_tension;
    conver_and_send_data(roller_data, sizeof(float)*3, ROLLER_DATA_TYPE);
    float imu_data_list [10];
    imu_data_list[0] = my_imu->imu_measurement.accel.x;
    imu_data_list[1] = my_imu->imu_measurement.accel.y;    
    imu_data_list[2] = my_imu->imu_measurement.accel.z;    
    imu_data_list[3] = my_imu->imu_measurement.gyro.x;
    imu_data_list[4] = my_imu->imu_measurement.gyro.y;    
    imu_data_list[5] = my_imu->imu_measurement.gyro.z;
    imu_data_list[6] = my_imu->imu_measurement.quaternion.q0;
    imu_data_list[7] = my_imu->imu_measurement.quaternion.q1;
    imu_data_list[8] = my_imu->imu_measurement.quaternion.q2;
    imu_data_list[9] = my_imu->imu_measurement.quaternion.q3;
    conver_and_send_data(imu_data_list, sizeof(float)*10, IMU_TYPE);







}


void sender::conver_and_send_data(float* data, size_t size,char type) {
    uint8_t bytes[size];
    memcpy(bytes, data, size);
    socketSession->emitTyped(bytes,size,type);
}
