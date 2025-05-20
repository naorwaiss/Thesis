#ifndef DIFF_ROBOT_H
#define DIFF_ROBOT_H

#include <vector>
#include <cstdint>
#include <Dynamixel2Arduino.h>
#include <HardwareSerial.h>
#include <Arduino.h>

#define MOTOR_COUNT 6


struct MotorFeedback {
    /*
    struct the andle the motor feedback data -> this struck call from the sender to send data
    */
    std::vector<float> current;
    std::vector<float> speed;
    std::vector<int> encoderPosition_direct_read;
    std::vector<float> encoderPosition_absolute_read;
    std::vector<uint8_t> error_state;

    MotorFeedback(int size) {
        current.resize(size);
        speed.resize(size);
        encoderPosition_direct_read.resize(size);
        encoderPosition_absolute_read.resize(size);
        error_state.resize(size);
    }
};



class Diff_Robot
{
private:

    uint8_t front_right;
    uint8_t front_left;
    uint8_t rear_right_1;
    uint8_t rear_right_2;
    uint8_t rear_left_1;
    uint8_t rear_left_2;
    uint8_t dir_pin_dxl;
    HardwareSerial& serial_dxl;
    Dynamixel2Arduino dxl;
    const float DXL_PROTOCOL_VERSION = 2.0;
public:
    MotorFeedback feedback;
    float v, w;
    Diff_Robot(uint8_t front_right, uint8_t front_left, uint8_t rear_right_1,
               uint8_t rear_right_2, uint8_t rear_left_1, uint8_t rear_left_2,
               uint8_t dir_pin, HardwareSerial& serial);

    void init();
    void main_loop();
    void get_feedback();
    void set_velocity(float v, float w);
};

#endif