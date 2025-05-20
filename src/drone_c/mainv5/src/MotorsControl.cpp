#include <Arduino.h>
#include "Var_types.h"
#include "MotorsControl.h"

MeanFilter PWM_filter(8);

// Initialization of the motors
void Motors::Motors_init() {
    // Set the PWM resolution for the ESCs
    
    // Setting the motor pins as output
    pinMode(Motor_struct.M1_pin, OUTPUT);
    pinMode(Motor_struct.M2_pin, OUTPUT);
    pinMode(Motor_struct.M3_pin, OUTPUT);
    pinMode(Motor_struct.M4_pin, OUTPUT);
    
    delay(100);
    
    // Set the PWM frequency for the ESCs. All pins are connected to the same timer, setting the frequency for one pin will set it for all.
    analogWriteFrequency(Motor_struct.M1_pin, ESC_FREQUENCY);
    analogWriteResolution(12);
    analogWriteFrequency(Motor_struct.M2_pin, ESC_FREQUENCY);
    analogWriteResolution(12);
    analogWriteFrequency(Motor_struct.M3_pin, ESC_FREQUENCY);
    analogWriteResolution(12);
    analogWriteFrequency(Motor_struct.M4_pin, ESC_FREQUENCY);
    analogWriteResolution(12);

    delay(100);
}

// Arm Function
void Motors::Arm() {
    // Set the PWM value for the ESCs
    analogWrite(Motor_struct.M1_pin, MOTOR_ARM);
    analogWrite(Motor_struct.M2_pin, MOTOR_ARM);
    analogWrite(Motor_struct.M3_pin, MOTOR_ARM);
    analogWrite(Motor_struct.M4_pin, MOTOR_ARM);
}

// Disarm Function
void Motors::Disarm() {
    // Set the PWM value for the ESCs
    analogWrite(Motor_struct.M1_pin, MOTOR_OFF);
    analogWrite(Motor_struct.M2_pin, MOTOR_OFF);
    analogWrite(Motor_struct.M3_pin, MOTOR_OFF);
    analogWrite(Motor_struct.M4_pin, MOTOR_OFF);
}

void Motors::set_motorPWM() {
    // Set the PWM value for the ESCs
    analogWrite(Motor_struct.M1_pin, Motor_struct.PWM1+50);
    analogWrite(Motor_struct.M2_pin, Motor_struct.PWM2);
    analogWrite(Motor_struct.M3_pin, Motor_struct.PWM3);
    analogWrite(Motor_struct.M4_pin, Motor_struct.PWM4);
}

void Motors::Motor_Mix(attitude_t motor_input, int throttle) {
    Motor_struct.PWM1 = throttle - motor_input.roll - motor_input.pitch - motor_input.yaw;
    Motor_struct.PWM2 = throttle - motor_input.roll + motor_input.pitch + motor_input.yaw;
    Motor_struct.PWM3 = throttle + motor_input.roll + motor_input.pitch - motor_input.yaw;
    Motor_struct.PWM4 = throttle + motor_input.roll - motor_input.pitch + motor_input.yaw;
    PWM_filter.pushSample(0, Motor_struct.PWM1);
    PWM_filter.pushSample(1, Motor_struct.PWM2);
    PWM_filter.pushSample(2, Motor_struct.PWM3);
    PWM_filter.pushSample(3, Motor_struct.PWM4);

    Motor_struct.PWM1 = PWM_filter.getRowMean(0);
    Motor_struct.PWM2 = PWM_filter.getRowMean(1);
    Motor_struct.PWM3 = PWM_filter.getRowMean(2);
    Motor_struct.PWM4 = PWM_filter.getRowMean(3);

    // Constrain the values to be between 1100 and 1900
    Motor_struct.PWM1 = constrain(Motor_struct.PWM1, MOTOR_START, MOTOR_MAX);
    Motor_struct.PWM2 = constrain(Motor_struct.PWM2, MOTOR_START, MOTOR_MAX);
    Motor_struct.PWM3 = constrain(Motor_struct.PWM3, MOTOR_START, MOTOR_MAX);
    Motor_struct.PWM4 = constrain(Motor_struct.PWM4, MOTOR_START, MOTOR_MAX);

    Motor_struct.PWM1 = US_2_PULSE(Motor_struct.PWM1);
    Motor_struct.PWM2 = US_2_PULSE(Motor_struct.PWM2);
    Motor_struct.PWM3 = US_2_PULSE(Motor_struct.PWM3);
    Motor_struct.PWM4 = US_2_PULSE(Motor_struct.PWM4);

    // Serial.print(Motor_struct.PWM1);Serial.print("  ");
    // Serial.print(Motor_struct.PWM2);Serial.print("  ");
    // Serial.print(Motor_struct.PWM3);Serial.print("  ");
    // Serial.print(Motor_struct.PWM4);Serial.println("  ");

}

motor_t Motors::Get_motor() {
    return Motor_struct;
}