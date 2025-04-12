#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <Arduino.h>
#include <cmath>
#include "eigen.h"
#include "Var_types.h"


#define MOTOR_NUMBER 4

struct MeanFilter {
    /*
    struct the andle the motor speed sample and make mean filter to the data -> for type 1
    */
    int sample;
    Eigen::MatrixXf sum;

    MeanFilter(int sample)
        : sample(sample), sum(Eigen::MatrixXf::Zero(MOTOR_NUMBER, sample)) {}

    void printMatrix() const {
        for (int i = 0; i < sum.rows(); ++i) {
            for (int j = 0; j < sum.cols(); ++j) {
                Serial.print(sum(i, j), 4);
                Serial.print("\t");
            }
            Serial.println();
        }
        Serial.println();
    }

    // Push a new value to a specific motor row
    void pushSample(int motor_index, float value) {
        if (motor_index < 0 || motor_index >= sum.rows()) return;

        // Shift all values to the right
        for (int j = sample - 1; j > 0; --j) {
            sum(motor_index, j) = sum(motor_index, j - 1);
        }
        sum(motor_index, 0) = value;
    }

    float getRowMean(int motor_index) const {
        if (motor_index < 0 || motor_index >= sum.rows()) return 0.0f;

        float row_sum = 0.0f;
        for (int j = 0; j < sample; ++j) {
            row_sum += sum(motor_index, j);
        }
        return row_sum / sample;
    }
};

// extern MeanFilter PWM_filter;



class Motors {
    private:
     int MOTOR_OFF = 1000;
     int MOTOR_ARM = 1100;
     #define PWM_PERIOD 1000000 / ESC_FREQUENCY  // Use ESC_FREQUENCY directly
     #define PWM_RESOLUTION 12
     #define PWM_MAX ((1 << PWM_RESOLUTION) - 1)
     #define US_2_PULSE(u) ((u) * PWM_MAX / (PWM_PERIOD))
     // #define MOTOR_START  1170
     #define MOTOR_START 1100
     #define MOTOR_MAX 2000
 
     motor_t Motor_struct;
 
    public:
     Motors(int motor1_pin, int motor2_pin, int motor3_pin, int motor4_pin) {
         Motor_struct.M1_pin = motor1_pin;
         Motor_struct.M2_pin = motor2_pin;
         Motor_struct.M3_pin = motor3_pin;
         Motor_struct.M4_pin = motor4_pin;
         Motor_struct.PWM1 = MOTOR_OFF;
         Motor_struct.PWM2 = MOTOR_OFF;
         Motor_struct.PWM3 = MOTOR_OFF;
         Motor_struct.PWM4 = MOTOR_OFF;
         MeanFilter PWM_filter(4);
     };

    // MeanFilter PWM_filter;

    void Motors_init();
    void Arm();
    void Disarm();
    void set_motorPWM();
    void Motor_Mix(attitude_t, int);
    motor_t Get_motor();
 };

#endif  // _MOTORS_CONTROL_H_