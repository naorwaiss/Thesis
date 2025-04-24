#ifndef LIDAR_CLASS_H
#define LIDAR_CLASS_H

#include <Arduino.h>
#include "RTCom/RTCom.h"

struct lidar_class_data {
    float angle;     // Angle in degrees
    float distance;  // Distance in meters
};

class lidar_class {
   private:
    static RTComSession* socketSession;

   public:
    lidar_class_data* lidar_class::measurement = nullptr;  // Pointer to the measurement data

    // Constructor
    explicit lidar_class(lidar_class_data* data, RTComSession* Session);
    void updateSession(RTComSession* newSession);
};

#endif