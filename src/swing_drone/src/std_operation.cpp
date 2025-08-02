#include "swing_drone/std_operation.hpp"

std_operation::std_operation(joy_data* joy_read) {
    _joy_read = joy_read;
}

drone_mod std_operation::mode_switch() {
    drone_mod return_mode;
    if (_joy_read->mode < 1500) {
        return_mode = drone_mod::rate_mode;
    } else {
        return_mode = drone_mod::backstepping;
    }
    return return_mode;
}

bool std_operation::arm_state() {
    if (_joy_read->aux_1_arm < 1500) {
        arm_info = arm_statuse::dis_arm;
        // publish here the zero to the velocity
        return false;
    } else {
        arm_info = arm_statuse::arm;
        return true;
    }
}
