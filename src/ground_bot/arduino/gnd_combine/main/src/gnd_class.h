#ifndef GND_CLASS_H
#define GND_CLASS_H


#include <Encoder.h>

#define RADIOUS_MM 122.5
#define PPR 1000

struct Motor_Data {
    uint8_t pwmh_pin;
    uint8_t dir_pin;
    uint8_t encoderA_pin;
    uint8_t encoderB_pin;
    bool direction;
    long encoder_read;
    float omega_dot;
    float pwm_value;
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

struct Robot_Data {
    float omega_dot_cmmand;
    float x_dot_cmmand;
    float x_dot_estimate;
    float y_dot_estimate;
};

class gnd_bot {
    public:
        Motor_Data right_motor;
        Motor_Data left_motor;
        Encoder right_encoder;
        Encoder left_encoder;
        Robot_Data robot;
        gnd_bot(double dt_loop,uint8_t pwmh_right, uint8_t dir_right, uint8_t pwmh_left, uint8_t dir_left, uint8_t encoderA_right, uint8_t encoderB_right, uint8_t encoderA_left, uint8_t encoderB_left);
        void set_alfa_beta(float alfa, float beta);
        void set_pid_param(float Kp, float Ki, float Kd);
        void init();
        void main(float omega_dot,float x_dot);
        void get_velocity_prediction(Motor_Data &motor, Encoder &encoder);
        void open_loop_pwm(uint16_t axis_data, Motor_Data &motor);
    private:
      double dt_sec;
};




#endif
