#ifndef VAR_TYPES_H
#define VAR_TYPES_H

#include <Arduino.h>

#define ESC_FREQUENCY 500  // Frequency of the ESCs

// Frequencies to be used with the RATE_DO_EXECUTE_HZ macro. Do NOT use an arbitrary number.
#define RATE_1000_HZ 1000
#define RATE_500_HZ 500
#define RATE_250_HZ 250
#define RATE_100_HZ 100
#define RATE_50_HZ 50
#define RATE_25_HZ 25

#define RATE_MAIN_LOOP RATE_1000_HZ
#define ATTITUDE_RATE RATE_500_HZ
#define POSITION_RATE RATE_100_HZ
#define RATE_HL_COMMANDER RATE_100_HZ
#define RATE_SUPERVISOR RATE_25_HZ


#define rad2deg 180.0f/PI
#define PI 3.14159265358979323846f
#define deg2rad PI / 180.0f


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

// Notch filter data structure
typedef struct notch_filter_s {
    float coeffs_a[3];  // IIR coefficients
    float coeffs_b[3];  // FIR coefficients
    float inputs[3];    // Input history
    float outputs[3];   // Output history
} notch_filter_t;

// Sensor filtering data structure
typedef struct filter_data_s {
    notch_filter_t acc_x_notch;
    notch_filter_t acc_y_notch;
    notch_filter_t acc_z_notch;
    vec3_t acc_filtered;
    vec3_t gyro_filtered;
    vec3_t mag_filtered;
} filter_data_t;

typedef struct {
    vec3_t acc;
    vec3_t acc_LPF = {0.0, 0.0, 0.0};
    vec3_t acc_bias = {0.0, 0.0, 0.0};
    vec3_t gyro;
    vec3_t gyro_bias = {0.0, 0.0, 0.0};
    vec3_t gyro_HPF = {0.0, 0.0, 0.0};
    vec3_t gyro_LPF = {0.0, 0.0, 0.0};
    vec3_t mag;
    vec3_t mag_LPF = {0.0, 0.0, 0.0};
    vec3_t mag_bias = {0.0, 0.0, 0.0};
    vec3_t initial_mag = {0.0, 0.0, 0.0};
    float initial_heading = 0.0;
    baro_t baro_data;
    filter_data_t filter_data;  // Added filter data structure
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

typedef struct state_s {
    attitude_t attitude_angles;
    quat_t attitudeQuaternion;
    float height;
    vec3_t velocity;
    vec3_t position;
    vec3_t acceleration;
} state_t;

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
    float Imax_roll;
    float Imax_pitch;
    float Imax_yaw;

} PID_Params_t;

typedef struct PID_out_s {
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

#endif