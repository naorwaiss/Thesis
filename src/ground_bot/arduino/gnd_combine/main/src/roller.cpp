#include "roller.h"

roller::roller(double dt_sec, uint8_t ENA_ARRIVE, uint8_t INA_PIN_ARRIVE, uint8_t INB_PIN_ARRIVE, uint8_t PWM_PIN_ARRIVE, uint8_t DOUT_ARRIVE, uint8_t CLK_ARRIVE) {
    INA_PIN = INA_PIN_ARRIVE;
    INB_PIN = INB_PIN_ARRIVE;
    PWM_PIN = PWM_PIN_ARRIVE;
    ENA_PIN = ENA_ARRIVE;
    DOUT = DOUT_ARRIVE;
    CLK = CLK_ARRIVE;
    this->dt = dt_sec;
}

void roller::init_roller_motor() {
    pinMode(ENA_PIN, OUTPUT);
    pinMode(INA_PIN, OUTPUT);
    pinMode(INB_PIN, OUTPUT);
    pinMode(PWM_PIN, OUTPUT);
}

void roller::stopMotor() {
    digitalWrite(ENA_PIN, LOW);
    digitalWrite(INA_PIN, LOW);
    digitalWrite(INB_PIN, LOW);
    analogWrite(PWM_PIN, 0);
    pid.sum_error = 0;
    pid.previous_error = 0;
}

void roller::motor_control(int pwm) {
    int pwm_const = constrain(pwm, -255, 255);
    int dir = pwm_const > 0 ? 1 : 2;
    switch (dir) {
        case 1:
            digitalWrite(ENA_PIN, HIGH);
            digitalWrite(INA_PIN, HIGH);
            digitalWrite(INB_PIN, LOW);
            analogWrite(PWM_PIN, abs(pwm_const));
            break;
        case 2:
            digitalWrite(ENA_PIN, HIGH);
            digitalWrite(INA_PIN, LOW);
            digitalWrite(INB_PIN, HIGH);
            analogWrite(PWM_PIN, abs(pwm_const));
            break;
    }
}

void roller::direction_find() {
    if (load_cell.tension > load_cell.dis_tension + load_cell.threshold_tension) {
        position = Direction_enum::UP;
    } else if (load_cell.tension < load_cell.dis_tension - load_cell.threshold_tension) {
        position = Direction_enum::DOWN;
    } else {
        position = Direction_enum::MIDDLE;
    }
}

void roller::error_find() {
    switch (position) {
        case Direction_enum::UP:
            load_cell.error = load_cell.tension - load_cell.dis_tension;
            break;
        case Direction_enum::DOWN:
            load_cell.error = load_cell.tension - load_cell.dis_tension;
            load_cell.error *= 1.75;
            break;
        case Direction_enum::MIDDLE:
            load_cell.error = 0;
            break;
    }
}

void roller::applyMotorControl(float control) {
    int pwmOut = abs(pid.control);
    pwmOut = constrain(pwmOut, 0, 255);
    digitalWrite(ENA_PIN, HIGH);
    if (pid.control > 0) {
        digitalWrite(INA_PIN, HIGH);
        digitalWrite(INB_PIN, LOW);
        analogWrite(PWM_PIN, pwmOut);
    } else if (pid.control < 0) {
        digitalWrite(INA_PIN, LOW);
        digitalWrite(INB_PIN, HIGH);
        analogWrite(PWM_PIN, pwmOut);
    } else {
        stopMotor();
    }
}

void roller::set_pid_param(float Kp, float Ki, float Kd) {
    pid.Kp = Kp;
    pid.Ki = Ki;
    pid.Kd = Kd;
}

float roller::PID_control() {
    float control = 0;
    Serial.println(dt, 6);
    pid.sum_error += load_cell.error * (dt);
    pid.sum_error = constrain(pid.sum_error, -pid.sum_errorMax, pid.sum_errorMax);
    float derivative = (load_cell.error - pid.previous_error) * (1 / dt);
    pid.previous_error = load_cell.error;
    control = pid.Kp * load_cell.error + pid.Ki * pid.sum_error + pid.Kd * derivative;
    return control;
}

void roller::init_roller() {
    load_cell_sensor.begin(DOUT, CLK);
    analogWriteFrequency(PWM_PIN, 20000);
    init_roller_motor();
    stopMotor();
    Serial.println("roller motor initialized");
}

void roller::main_roller() {
    load_cell.raw_Data = load_cell_sensor.get_value();
    load_cell.tension = constrain(-1*(load_cell.raw_Data - load_cell.rawEmpty) / load_cell.load_ScaleFactor, 0, 50);
    direction_find();
    error_find();
    pid.control = PID_control();
    applyMotorControl(pid.control);
}
