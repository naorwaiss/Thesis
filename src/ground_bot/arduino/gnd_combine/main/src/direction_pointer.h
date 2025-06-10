#ifndef DIRECTIONPOINTER_H
#define DIRECTIONPOINTER_H

#include "Encoder.h"
#include <Arduino.h>
#include "var_type.h"



class DIRPOINTER {
   private:
    uint8_t _encoder_a;
    uint8_t _encoder_b;
    uint8_t _analog_pin_pitch;
    uint8_t _analog_pin_yaw;
    Encoder _motorEncoder;
    ALFA_BETA_FILTER velo_filter;
    double _dt_sec;
    const float _ROOLER_RADIUS_M = 0.0305;  // need to check the length 
    const float _PPR = 1425.1;              // Pulses Per Revolution
    const int _POT_MIN = 0;
    const int _POT_MAX = 1023;
    const float _YAW_MIN_DEG = 0.0;  // לבדוק איזה זווית מתאימה למה ולהכניס את הערכים
    const float _YAW_MAX_DEG = 180.0;
    const float _PITCH_MIN_DEG = 0.0;
    const float _PITCH_MAX_DEG = 90.0;

   public:
    DIRPOINTER(double dt_sec,uint8_t encoder_a, uint8_t encoder_b, uint8_t analog_pin_pitch, uint8_t analog_pin_yaw);
    void main_DirPointer();
};

#endif
