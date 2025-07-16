#ifndef VOLTMETER_H
#define VOLTMETER_H

#include "Arduino.h"
#include "Var_types.h"
#include "drone_identify.h"

class Voltmeter {
    public:
        Voltmeter(Drone_Data_t *drone_data ,int voltmeterPin, int currentPin);
        void read_bat_data();
        void init_voltmeter();

    private:
        Drone_Data_t *_drone_data;
        int _voltmeterPin;
        int _currentPin;
        float  _voltmeter_calibration_factor;
        float _current_calibration_factor;
        float _current_bias;

};
#endif
