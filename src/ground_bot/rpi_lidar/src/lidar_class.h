#ifndef LIDAR_CLASS_H
#define LIDAR_CLASS_H

#include <Arduino.h>
#include "RTCom/RTCom.h"
#include <HardwareSerial.h> // Add this if needed for your platform
#include <elapsedMillis.h> // Add this line at the top

struct lidar_data {
    float angle;     // Angle in degrees
    float distance;  // Distance in meters
};

class lidar_class {
   private:
    static RTComSession* socketSession;
    static lidar_data* measurement;
    HardwareSerial* lidarSerial; // Add this line
    int* pin;
    elapsedMicros lidar_timer;  // Timer for 10Hz control
    uint8_t lidar_data_byte[sizeof(float) * 2];

   public:
    // Constructor
    explicit lidar_class(lidar_data* data, RTComSession* socketSession ,HardwareSerial* Serial, int* motor_pin);
    void updateSession(RTComSession* newSession);
    void init_lidar();
    void sendStartScan();
    void send_lidar_data();
    // void updateSession(RTComSession* newSession);
    void take_lidar_data();
};

#endif