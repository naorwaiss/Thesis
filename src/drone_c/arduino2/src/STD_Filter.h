#ifndef STD_FILTER_H
#define STD_FILTER_H

#define GYRO_LPF_FREQ 300.0f  // Increase from 40.0f
#define ACC_LPF_FREQ GYRO_LPF_FREQ   // Increase from 10.0f
#define GYRO_HPF_FREQ 1.0f   // Lower from 2.5f to reduce drift removal aggressiveness
#define MAG_LPF_FREQ 50.0f   // Increase from 10.0f

#include <cmath>
#include <Arduino.h>
#include "Var_types.h"

class STD_Filter {
   public:
    STD_Filter(Measurement_t* meas_data, float sample_hz);
    void acc_low_pass_filter();
    void gyro_low_pass_filter();
    void gyro_high_pass_filter();
    void all_filter();

   private:
    Measurement_t* _meas_data;
    float _dt = 0.0f;
    vec3_t _gyroPrev = {0.0, 0.0, 0.0};
    float ALPHA_ACC_LPF = (2.0f * PI * ACC_LPF_FREQ * DT) / (2.0f * PI * ACC_LPF_FREQ * DT + 1.0f);
    float ALPHA_GYRO_LPF = (2.0f * PI * GYRO_LPF_FREQ * DT) / (2.0f * PI * GYRO_LPF_FREQ * DT + 1.0f);
    float ALPHA_HPF = (1.0f / (2.0f * PI * GYRO_HPF_FREQ * DT + 1.0f));
    float ALPHA_MAG_LPF = (2.0f * PI * MAG_LPF_FREQ * DT) / (2.0f * PI * MAG_LPF_FREQ * DT + 1.0f);
};

#endif