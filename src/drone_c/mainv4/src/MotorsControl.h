#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <Arduino.h>
#include "Var_types.h"



class Motors {
    private:
        int MOTOR_OFF = 1000;
        int MOTOR_ARM = 1100;
        #define PWM_PERIOD 1000000/ESC_FREQUENCY  // Use ESC_FREQUENCY directly
        #define PWM_RESOLUTION 12
        #define PWM_MAX ((1 << PWM_RESOLUTION) - 1)
        #define US_2_PULSE(u) ((u)* PWM_MAX / (PWM_PERIOD))
        // #define MOTOR_START  1170
        #define MOTOR_START  1100



        motor_t Motor_struct;

    public:
        Motors(int motor1_pin, int motor2_pin, int motor3_pin, int motor4_pin){


            Motor_struct.M1_pin = motor1_pin;
            Motor_struct.M2_pin = motor2_pin;
            Motor_struct.M3_pin = motor3_pin;
            Motor_struct.M4_pin = motor4_pin;
            Motor_struct.PWM1 = MOTOR_OFF;
            Motor_struct.PWM2 = MOTOR_OFF;
            Motor_struct.PWM3 = MOTOR_OFF;
            Motor_struct.PWM4 = MOTOR_OFF;


        };
        void Motors_init();
        void Arm();
        void Disarm();
        void set_motorPWM();
        void Motor_Mix(attitude_t , int );
        motor_t Get_motor();

};

#endif // _MOTORS_CONTROL_H_