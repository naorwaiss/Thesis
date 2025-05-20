#ifndef ROLLER_H
#define ROLLER_H

#include <Arduino.h>
#include "HX711.h"

struct load_cell_t {
    const float minTension = 10;
    const float maxTension = 40;
    const float tension_threshold = 2;
    const long rawEmpty = 162592;
    const float load_ScaleFactor = (200400 - rawEmpty) / 39;
    float error = 0;
    long raw_Data;
    float tension;
};

struct PID {
    float Kp = 10;
    float Ki = 0;
    float Kd = 0;
    float previousError = 0;
    float integral = 0;
    float integralMax = 1000;
    float control = 0;
};

class roller {
   public:
    roller(double dt_sec, uint8_t ENA_ARRIVE, uint8_t INA_PIN_ARRIVE, uint8_t INB_PIN_ARRIVE, uint8_t PWM_PIN_ARRIVE, uint8_t DOUT_ARRIVE, uint8_t CLK_ARRIVE);
    load_cell_t load_cell;
    PID pid;
    HX711 load_cell_sensor;
    void init_roller();
    void init_roller_motor();
    void stopMotor();
    void motor_control(int pwm);
    void main_roller();
    void error_find();
    void applyMotorControl(float control);
    void set_pid_param(float Kp, float Ki, float Kd);
    float PID_control();

   private:
    uint8_t ENA_PIN;  // motor pin
    uint8_t INA_PIN;  // motor pin
    uint8_t INB_PIN;  // motor pin
    uint8_t PWM_PIN;  // motor pin
    uint8_t DOUT;     // load cell pin
    uint8_t CLK;      // load cell pin
    double dt;
};

#endif