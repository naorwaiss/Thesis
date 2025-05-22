#include "roller.h"

roller::roller(double dt_sec,uint8_t ENA_ARRIVE, uint8_t INA_PIN_ARRIVE, uint8_t INB_PIN_ARRIVE, uint8_t PWM_PIN_ARRIVE, uint8_t DOUT_ARRIVE, uint8_t CLK_ARRIVE) {
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
}

void roller::motor_control(int pwm) {
    digitalWrite(ENA_PIN, HIGH);   // הפעלת המנוע
    digitalWrite(INA_PIN, LOW);  // כיוון קדימה
    digitalWrite(INB_PIN, HIGH);   // כיוון קדימה
    analogWrite(PWM_PIN, pwm);    // מהירות 50%
}



// void roller::error_find() {
//     if (load_cell.tension < load_cell.minTension) {
//         load_cell.error = load_cell.minTension - load_cell.tension;  // need to tension
//     } else if (load_cell.tension > load_cell.maxTension) {
//         load_cell.error = load_cell.maxTension - load_cell.tension;  // need to release
//     } else {
//         load_cell.error = 0;
//     }
// }

void roller::error_find() {
    float error;
    error = load_cell.tension - load_cell.dis_tension;
    if (error > 0 && error < load_cell.threshold_tension) {
        error = 0;
        load_cell.error = error;
    } else if (error < 0 && error > -load_cell.threshold_tension) {
        error = 0;
        load_cell.error = error;
    } else {
        load_cell.error = error;
    }
}



void roller::applyMotorControl(float control) {
    int pwmOut = abs(pid.control);
    // if (pwmOut < 50 && pwmOut > 0) pwmOut = 50;
    pwmOut = constrain(pwmOut, 0, 255);
    Serial.print("pwmOut: ");
    Serial.println(pwmOut);
    if (pid.control > 0 ) {
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
    pid.integral += load_cell.error * (1 / dt);
    pid.integral = constrain(pid.integral, -pid.integralMax, pid.integralMax);
    float derivative = (load_cell.error - pid.previousError) * (1 / dt);
    pid.previousError += load_cell.error;
    control = pid.Kp * load_cell.error + pid.Ki * pid.integral + pid.Kd * derivative;
    // if (abs(control) < 25) control = 0;
    // if (abs(load_cell.error) < 5) control *= 0.5;    
    return control;
}


void roller::init_roller() {
    load_cell_sensor.begin(DOUT, CLK);
    analogWriteFrequency(PWM_PIN, 20000);
    init_roller_motor();
    // stopMotor();
    Serial.println("roller motor initialized");
}

void roller::main_roller() {
    load_cell.raw_Data = load_cell_sensor.get_value();
    load_cell.tension = (load_cell.raw_Data - load_cell.rawEmpty) / load_cell.load_ScaleFactor;
    if (load_cell.tension > -load_cell.threshold_tension && load_cell.tension < load_cell.threshold_tension) load_cell.tension = 0;
    error_find();
    pid.control = PID_control();
    Serial.print("pid.control: ");
    Serial.println(pid.control);
    applyMotorControl(pid.control);

    
}


