#ifndef LIDAR_CLASS_H
#define LIDAR_CLASS_H

#include <Arduino.h>

struct lidar_class_data {
    float angle;         // Angle in degrees
    float distance;      // Distance in meters
}; 



class lidar_class {
   private:
    lidar_class_data *data;  // Pointer to the data structure



   public:
   explicit lidar_class(lidar_class_data *data);



};

#endif