#include "sender.h"

RTComSession* sender::socketSession = nullptr;
gnd_bot* sender::my_bot = nullptr;
roller* sender::my_roller = nullptr;

sender::sender(RTComSession* session, gnd_bot* gnd_instance, roller* roller_instance) {
    socketSession = session;
    my_bot = gnd_instance;      
    my_roller = roller_instance;
}

void sender::update_session(RTComSession& newsession) {
    socketSession = &newsession;
}

void sender::convert_data() {
    float float_odom[2];
    float_odom[0] = my_bot->robot.x_dot_estimate;
    float_odom[1] = my_bot->robot.omega_dot_estimate;
    conver_and_send_data(float_odom, sizeof(float)*2, ODOM_TYPE);
    float float_twist[2];
    float_twist[0] = my_bot->robot.omega_dot_cmmand;
    float_twist[1] = my_bot->robot.x_dot_cmmand;
    conver_and_send_data(float_twist, sizeof(float)*2, TWIST_TYPE);
    float linear_velo[2];
    linear_velo[0] = my_bot->right_motor.wheel_linera_speed;
    linear_velo[1] = my_bot->left_motor.wheel_linera_speed;
    conver_and_send_data(linear_velo, sizeof(float)*2, LINEAR_VELO);
}


void sender::conver_and_send_data(float* data, size_t size,char type) {
    uint8_t bytes[size];
    memcpy(bytes, data, size);
    socketSession->emitTyped(bytes,size,type);
}
