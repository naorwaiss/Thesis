#ifndef DRONE_IDENTIFY_H
#define DRONE_IDENTIFY_H

#include "Var_types.h"

enum class DroneMode {
    MODE_RATE = 1,
    MODE_STABILIZE = 2,
};

enum class DroneFilter {
    COMPCLASS = 1,
    KALMAN = 2,
};

enum class Beta {
    // Those values define how much we rely on the accelerometer
    Std_factor = 1,
    Rely_more = 2,
    Rely_less = 3,
};



typedef struct {
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

typedef struct {
    float std_beta = 0.0f;
    float high_beta = 0.0f;
    float low_beta = 0.0f;
} magwick_data_t;


typedef struct {
    PID_const_t pid_const;
    magwick_data_t filter_data;
} drone_tune_t;

typedef struct {
    uint8_t mac[6];
    char name[10];
    DroneMode drone_mode = DroneMode::MODE_RATE;
    DroneFilter filter_mode = DroneFilter::COMPCLASS;
    bool is_armed = false;
    float voltage_reading = 0.0f;
    float current_reading = 0.0f;
} Drone_Data_t;

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
inline uint8_t mac2[6] = {0x04, 0xE9, 0xE5, 0x19, 0x2B, 0x2D};  // drone amit 
inline uint8_t mac3[6] = {0x04, 0xE9, 0xE5, 0x17, 0xE3, 0x91};  // drone amit - > pid not set yet

inline void getbot_param(drone_tune_t& myDrone_tune, Drone_Data_t& myDrone) {
    getMAC(myDrone.mac);
    if (compareMac(myDrone.mac, mac0) || compareMac(myDrone.mac, mac2)) {
        myDrone_tune.pid_const.defaultRrollPID = {0.7f, 0.05f, 0.3f};
        myDrone_tune.pid_const.defaultRpitchPID = {0.7f, 0.05f, 0.3f};
        myDrone_tune.pid_const.defaultRyawPID = {1.2f, 0.0f, 0.05f};
        myDrone_tune.pid_const.defaultImax_rate = {40.0f, 40.0f};
        myDrone_tune.pid_const.defaultSrollPID = {11.8f, 0.1f, 0.0f};
        myDrone_tune.pid_const.defaultSpitchPID = {11.8f, 0.1f, 0.0f};
        myDrone_tune.pid_const.defaultSyawPID = {4.0f, 0.0f, 0.0f};
        myDrone_tune.pid_const.defaultImax_stab = {25.0f, 25.0f};
        myDrone_tune.filter_data.std_beta = 0.1f;
        myDrone_tune.filter_data.high_beta = 0.2f;
        myDrone_tune.filter_data.low_beta = 0.05f;
        return;
    } else if (compareMac(myDrone.mac, mac2) || compareMac(myDrone.mac, mac3)) {
        myDrone_tune.pid_const.defaultRrollPID = {0.7f, 0.05f, 0.3f};
        myDrone_tune.pid_const.defaultRpitchPID = {0.7f, 0.05f, 0.3f};
        myDrone_tune.pid_const.defaultRyawPID = {1.2f, 0.00f, 0.05f};
        myDrone_tune.pid_const.defaultImax_rate = {40.0f, 40.0f};
        myDrone_tune.pid_const.defaultSrollPID = {0.1f, 0.0f, 0.0f};
        myDrone_tune.pid_const.defaultSpitchPID = {0.1f, 0.0f, 0.0f};
        myDrone_tune.pid_const.defaultSyawPID = {4.0f, 0.0f, 0.0f};
        myDrone_tune.pid_const.defaultImax_stab = {25.0f, 25.0f};
        myDrone_tune.filter_data.std_beta = 0.1f;
        myDrone_tune.filter_data.high_beta = 0.2f;
        myDrone_tune.filter_data.low_beta = 0.05f;
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
