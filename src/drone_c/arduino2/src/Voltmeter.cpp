#include "Voltmeter.h"

Voltmeter::Voltmeter(Drone_Data_t *drone_data ,int voltmeterPin, int currentPin) {
    _drone_data = drone_data;
    _voltmeterPin = voltmeterPin;
    _currentPin = currentPin;
}

void Voltmeter::read_bat_data() {
    analogReadResolution(12);  // Set the resolution to 12 bits

    _drone_data->voltage_reading = (float)analogRead(_voltmeterPin) / _voltmeter_calibration_factor;
    // Serial.println(_drone_data->voltage_reading);
    _drone_data->current_reading = ((float)analogRead(_currentPin))/ _current_calibration_factor + _current_bias;
    // Serial.println(_drone_data->current_reading);

}


void Voltmeter::init_voltmeter(){
    _voltmeter_calibration_factor = _drone_data->voltage_current_factors.x;
    _current_calibration_factor = _drone_data->voltage_current_factors.y;
    _current_bias = _drone_data->voltage_current_factors.z;




}





