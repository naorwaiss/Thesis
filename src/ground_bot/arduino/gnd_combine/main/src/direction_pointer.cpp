#include "direction_pointer.h"

DIRPOINTER::DIRPOINTER(double dt_sec, uint8_t encoder_a, uint8_t encoder_b, uint8_t analog_pin_pitch, uint8_t analog_pin_yaw)
    : _motorEncoder(encoder_a, encoder_b),
      velo_filter(dt_sec, 0.85, 0.1) {
    _encoder_a = encoder_a;
    _encoder_b = encoder_b;
    _analog_pin_pitch = analog_pin_pitch;
    _analog_pin_yaw = analog_pin_yaw;
}

void DIRPOINTER::main_DirPointer() {
    velo_filter.alfa_beta_calc(static_cast<float>(_motorEncoder.read()));
    float yawDeg = map(analogRead(_analog_pin_yaw), _POT_MIN, _POT_MAX, _YAW_MIN_DEG, _YAW_MAX_DEG);
    float pitchDeg = map(analogRead(_analog_pin_pitch), _POT_MIN, _POT_MAX, _PITCH_MIN_DEG, _PITCH_MAX_DEG);
    // need to fix this function with alfa beta and etc
}
