#ifndef VAR_TYPES_H
#define VAR_TYPES_H

#include <Arduino.h>
#include <string>
#include <array>

#define ESC_FREQUENCY 500  // Frequency of the ESCs

static const float SAMPLE_RATE = 833.0f;
static const float DT = 1.0f / SAMPLE_RATE;

// Frequencies to be used with the RATE_DO_EXECUTE_HZ macro. Do NOT use an arbitrary number.

#ifndef PI
#define PI 3.14159265358979323846f
#endif
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

typedef struct {
    uint8_t mac[6];
    std::array<float, 3> defaultRrollPID;  // DO NOT GO OVER Kd=0.9 !!!! Drone will kill someone!!!
    std::array<float, 3> defaultRpitchPID;
    std::array<float, 3> defaultRyawPID;
    std::array<float, 2> defaultImax_rate;

    // STABILIZE mode parameter values
    std::array<float, 3> defaultSrollPID;
    std::array<float, 3> defaultSpitchPID;
    std::array<float, 3> defaultSyawPID;
    std::array<float, 2> defaultImax_stab;
} PID_const_t;

inline void getMAC(uint8_t* pMacAddress) {
    for (uint8_t i = 0; i < 2; i++)
        pMacAddress[i] = (HW_OCOTP_MAC1 >> ((1 - i) * 8)) & 0xFF;
    for (uint8_t i = 0; i < 4; i++)
        pMacAddress[i + 2] = (HW_OCOTP_MAC0 >> ((3 - i) * 8)) & 0xFF;
}

inline void printMac(uint8_t* pMacAddress) {
    printf("MAC Address = %02X:%02X:%02X:%02X:%02X:%02X\r\n", pMacAddress[0], pMacAddress[1], pMacAddress[2], pMacAddress[3], pMacAddress[4], pMacAddress[5]);
}

inline bool compareMac(uint8_t mac1[6], uint8_t mac2[6]) {
    for (int i = 0; i < 6; i++) {
        if (mac1[i] != mac2[i]) {
            return false;
        }
    }
    return true;
}

inline uint8_t mac0[6] = {0x04, 0xE9, 0xE5, 0x18, 0xEE, 0x80};  // drone naor

inline void getbot_param(PID_const_t& myDrone) {
    getMAC(myDrone.mac);
    if (compareMac(myDrone.mac, mac0)) {
        myDrone.defaultRrollPID = {1.6f, 0.15f, 0.95f};
        myDrone.defaultRpitchPID = {1.6f, 0.15f, 0.95f};
        myDrone.defaultRyawPID = {2.0f, 0.0f, 0.05f};
        myDrone.defaultImax_rate = {100.0f, 100.0f};
        myDrone.defaultSrollPID = {10.0f, 0.01f, 0.0f};
        myDrone.defaultSpitchPID = {9.0f, 0.01f, 0.0f};
        myDrone.defaultSyawPID = {4.0f, 0.0f, 0.0f};
        myDrone.defaultImax_stab = {100.0f, 100.0f};
        return;
    } else {
        while (1) {
            Serial.print("Unknown MAC Address ");
            printMac(myDrone.mac);
            delay(1000);
        }
    }
}

#endif
