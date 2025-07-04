#include "Voltmeter.h"

Voltmeter::Voltmeter(Drone_Data_t *drone_data ,int voltmeterPin, int currentPin , int voltmeter_calibration_factor) {
    _drone_data = drone_data;
    _voltmeterPin = voltmeterPin;
    _currentPin = currentPin;
    _voltmeter_calibration_factor = voltmeter_calibration_factor;
}

void Voltmeter::read_bat_data() {
    _drone_data->voltage_reading = (float)analogRead(_voltmeterPin) / _voltmeter_calibration_factor;
    _drone_data->current_reading = (float)analogRead(_currentPin);
}
