#include "Diff_Robot.h"





Diff_Robot::Diff_Robot(uint8_t front_right, uint8_t front_left, uint8_t rear_right_1,
     uint8_t rear_right_2, uint8_t rear_left_1, uint8_t rear_left_2, uint8_t dir_pin, HardwareSerial& serial) :
     serial_dxl(serial),
     dxl(serial, dir_pin)
{
    this->front_right = front_right;
    this->front_left = front_left;
    this->rear_right_1 = rear_right_1;
    this->rear_right_2 = rear_right_2;
    this->rear_left_1 = rear_left_1;
    this->rear_left_2 = rear_left_2;
    this->dir_pin_dxl = dir_pin;
    feedback = MotorFeedback(MOTOR_COUNT);
}

void Diff_Robot::init() {
    dxl.begin(57600);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    dxl.ping(rear_right_1);
    dxl.torqueOff(rear_right_1);
    dxl.setOperatingMode(rear_right_1, OP_VELOCITY);
    dxl.torqueOn(rear_right_1);

    dxl.ping(rear_right_2);
    dxl.torqueOff(rear_right_2);
    dxl.setOperatingMode(rear_right_2, OP_VELOCITY);
    dxl.torqueOn(rear_right_2);

    dxl.ping(rear_left_1);
    dxl.torqueOff(rear_left_1);
    dxl.setOperatingMode(rear_left_1, OP_VELOCITY);
    dxl.torqueOn(rear_left_1);

    dxl.ping(rear_left_2);
    dxl.torqueOff(rear_left_2);
    dxl.setOperatingMode(rear_left_2, OP_VELOCITY);
    dxl.torqueOn(rear_left_2);

    dxl.ping(front_right);
    dxl.torqueOff(front_right);
    dxl.setOperatingMode(front_right, OP_POSITION);
    dxl.torqueOn(front_right);

    dxl.ping(front_left);
    dxl.torqueOff(front_left);
    dxl.setOperatingMode(front_left, OP_POSITION);
    dxl.torqueOn(front_left);
}

void Diff_Robot::main_loop() {

}