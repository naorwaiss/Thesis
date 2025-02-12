#include <Arduino.h>
// #include "RTCom/RTCom.h"
#include <AlfredoCRSF.h>
#include <Encoder.h>
#include "RTCom/RTCom.h"

#define NUM_CHANNELS 14
#define ENCODER_RESOLOTION 2252

#define BUF Serial.print("/ ")
#define down Serial.println()
#define crsfSerial Serial1  // Use Serial1 for the CRSF communication
#define RADIOUS_MM 0.065
#define PPR 100
#define max_omga 20
#define max_linear 20 * RADIOUS_MM

#define PWM_LATER 'P'
#define LINEAR_VELO 'L'
#define OMEGA 'O'

struct Motor_Data {
    const int pwmh_pin;
    const int dir_pin;
    int pwm_value;
    bool direction;
    const int encoderA_pin;
    const int encoderB_pin;
    long encoder_read;
    float omega_dot;
    float xk_1 = 0, vk_1 = 0, xk = 0, vk = 0, rk = 0;
    float a = 0.85, b = 0.005;
    float wheel_linera_speed;
    float prev_error = 0.0;
    float integral = 0.0;
    float pid_out = 0.0;
    float Kp;
    float Ki;
    float Kd;
};

#ifndef GND_BOT_H
#define GND_BOT_H

constexpr uint8_t SOCKET_IP_ADDRESS[] = {192, 168, 1, 198};
constexpr uint16_t SOCKET_PORT_NUMBER = 8888;
const RTComConfig SOCKET_CONFIG(1, 100, 200, 500);

namespace G_BOT {

extern Motor_Data right_motor;
extern Motor_Data left_motor;

const SocketAddress SOCKET_ADDRESS = SocketAddress(SOCKET_IP_ADDRESS, SOCKET_PORT_NUMBER);
extern RTCom rtcomSocket;
extern RTComSession *socketSession;

void open_loop_pwm(uint16_t axis_data, Motor_Data &motor);
void get_velocity_prediction(Motor_Data &motor, Encoder &encoder, double dt);
int motor_pid_omega(double dt, uint16_t axis_data);
void emit_data();
void executed_ch();
void onConnection(RTComSession &session);
void init();
void main();

}  // namespace G_BOT

#endif
