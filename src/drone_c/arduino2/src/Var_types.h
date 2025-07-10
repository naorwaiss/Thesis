#ifndef VAR_TYPES_H
#define VAR_TYPES_H

#include <Arduino.h>
#include <string>
#include <array>
#include "drone_identify.h"
// #define ESC_FREQUENCY 500  // Frequency of the ESCs
const float G = 9.80665; // Gravity constant in m/s^2
#define ESC_FREQUENCY 400
#define STAB_FREQUENCY ESC_FREQUENCY / 2  // Frequency of the STAB

static const float SAMPLE_RATE = 416.0f;
static const float DT = 1.0f / SAMPLE_RATE;

const unsigned long STAB_PERIOD = 1000000 / STAB_FREQUENCY;  // 200 Hz period in microseconds
const unsigned long MOTOR_PERIOD = 1000000 / ESC_FREQUENCY;  // 1,000,000 us / frequency in Hz
const unsigned long IMU_PERIOD = 1000000 / SAMPLE_RATE;
const unsigned long SEND_DATA_PERIOD = 1000000 / 50;  // 50 Hz


#define ELRSSerial Serial1  // Use Serial1 for the CRSF communication
#define MOTOR1_PIN 2        // front right
#define MOTOR2_PIN 3        // back right
#define MOTOR3_PIN 4        // back left
#define MOTOR4_PIN 5        // fron left
#define MAX_ANGLE 10.0f
#define MAX_RATE 200.0f
#define CONTROLLER_MIN 988
#define CONTROLLER_MAX 2012
#define CONTROLL_THR_MAX 1520
#define CONTROLL_THR_MIN 1480


// #define PI 3.14159265358979323846f
#define deg2rad PI / 180.0f
#define rad2deg 180.0f / PI

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} quat_t;

typedef struct baro_s {
    float pressure;     // mbar
    float temperature;  // degree Celcius
    float asl;          // m (ASL = altitude above sea level)
} baro_t;

typedef struct {
    vec3_t acc;
    vec3_t acc_LPF = {0.0, 0.0, 0.0};
    vec3_t acc_bias = {0.0, 0.0, 0.0};
    vec3_t gyroRAD;
    vec3_t gyroDEG;
    vec3_t gyro_bias = {0.0, 0.0, 0.0};
    vec3_t gyro_HPF = {0.0, 0.0, 0.0};
    vec3_t gyro_LPF = {0.0, 0.0, 0.0};
    vec3_t mag;
    vec3_t mag_LPF = {0.0, 0.0, 0.0};
    vec3_t mag_bias = {0.0, 0.0, 0.0};
    vec3_t initial_mag = {0.0, 0.0, 0.0};
    float initial_heading = 0.0;
    baro_t baro_data;
} Measurement_t;

typedef struct attitude_s {
    float roll;
    float pitch;
    float yaw;
} attitude_t;

// Specify addition operator for attitude_t: attitude_t + attitude_t
inline attitude_t operator+(const attitude_t& a, const attitude_t& b) {
    attitude_t result;
    result.roll = a.roll + b.roll;
    result.pitch = a.pitch + b.pitch;
    result.yaw = a.yaw + b.yaw;
    return result;
}

// Specify addition operator for attitude_t: attitude_t - attitude_t
inline attitude_t operator-(const attitude_t& a, const attitude_t& b) {
    attitude_t result;
    result.roll = a.roll - b.roll;
    result.pitch = a.pitch - b.pitch;
    result.yaw = a.yaw - b.yaw;
    return result;
}

// Specify multiplication operator for attitude_t: A * attitude_t
inline attitude_t operator*(const float A, const attitude_t& b) {
    attitude_t result;
    result.roll = A * b.roll;
    result.pitch = A * b.pitch;
    result.yaw = A * b.yaw;
    return result;
}

// Attitude + vec3_t
inline attitude_t operator+(const attitude_t& a, const vec3_t& b) {
    attitude_t result;
    result.roll = a.roll + b.x;
    result.pitch = a.pitch + b.y;
    result.yaw = a.yaw + b.z;
    return result;
}

// Attitude - vec3_t
inline attitude_t operator-(const attitude_t& a, const vec3_t& b) {
    attitude_t result;
    result.roll = a.roll - b.x;
    result.pitch = a.pitch - b.y;
    result.yaw = a.yaw - b.z;
    return result;
}

// Specify the `+=` operator for attitude_t
inline attitude_t& operator+=(attitude_t& a, attitude_t& b) {
    a.roll += b.roll;
    a.pitch += b.pitch;
    a.yaw += b.yaw;
    return a;
}

// Specify the `-=` operator for attitude_t
inline attitude_t& operator-=(attitude_t& a, attitude_t& b) {
    a.roll -= b.roll;
    a.pitch -= b.pitch;
    a.yaw -= b.yaw;
    return a;
}

typedef struct PID_Params_s {
    float RollP;
    float RollI;
    float RollD;
    float PitchP;
    float PitchI;
    float PitchD;
    float YawP;
    float YawI;
    float YawD;
    // Those alphas are used for HPF to calculate the derivative term:
    float Alpha_roll;
    float Alpha_pitch;
    float Alpha_yaw;
    float RollD_tau;
    float PitchD_tau;
    float YawD_tau;
    float Imax_roll;
    float Imax_pitch;
    float Imax_yaw;

} PID_Params_t;

typedef struct PID_out_s {
    attitude_t error = {0.0, 0.0, 0.0};
    attitude_t P_term;
    attitude_t I_term;
    attitude_t D_term;
    attitude_t PID_ret = {0.0, 0.0, 0.0};
    attitude_t prev_err = {0.0, 0.0, 0.0};
    attitude_t prev_errHPF = {0.0, 0.0, 0.0};
    attitude_t prev_errLPF = {0.0, 0.0, 0.0};
    attitude_t prev_Iterm = {0.0, 0.0, 0.0};
    attitude_t prev_Dterm = {0.0, 0.0, 0.0};

} PID_out_t;

typedef struct motor_s {
    int M1_pin;
    int M2_pin;
    int M3_pin;
    int M4_pin;
    int PWM1;
    int PWM2;
    int PWM3;
    int PWM4;
} motor_t;

typedef struct Controller_s {
    int throttle;
    int roll;
    int pitch;
    int yaw;
    int aux1;
    int aux2;
    int aux3;
    int aux4;
} Controller_t;

typedef struct state_s {
    attitude_t attitude_angles;
    quat_t attitude_Quaternion;
    float height;
    vec3_t velocity;
    vec3_t position;
    vec3_t acceleration;
} state_t;

/////// pid config



#endif