#ifndef STD_FILTER_H
#define STD_FILTER_H

#define GYRO_LPF_FREQ 300.0f  // Increase from 40.0f
#define ACC_LPF_FREQ GYRO_LPF_FREQ   // Increase from 10.0f
#define GYRO_HPF_FREQ 1.0f   // Lower from 2.5f to reduce drift removal aggressiveness
#define MAG_LPF_FREQ 50.0f   // Increase from 10.0f

#include <cmath>
#include <Arduino.h>



struct SecondOrderLPF {
    float b0, b1, b2, a1, a2;
    float x1 = 0, x2 = 0, y1 = 0, y2 = 0;

    SecondOrderLPF(float sample_rate, float cutoff_freq, float damping = 0.707f) {
        float omega = 2.0f * PI * cutoff_freq / sample_rate;
        float sin_omega = sinf(omega);
        float cos_omega = cosf(omega);
        float alpha = sin_omega / (2.0f * damping);

        float a0 = 1.0f + alpha;

        b0 = ((1.0f - cos_omega) / 2.0f) / a0;
        b1 = (1.0f - cos_omega) / a0;
        b2 = b0;
        a1 = (-2.0f * cos_omega) / a0;
        a2 = (1.0f - alpha) / a0;

        x1 = x2 = y1 = y2 = 0.0f;  // reset state
    }

    float update(float x) {
        float y = b0 * x + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
        return y;
    }
};

#include "Var_types.h"

class STD_Filter {
   public:
    STD_Filter(Measurement_t* meas_data, float sample_hz);
    void acc_low_pass_filter();
    void gyro_low_pass_filter();
    void gyro_high_pass_filter();
    void all_filter();

   private:
    SecondOrderLPF gyro_x;
    SecondOrderLPF gyro_y;
    SecondOrderLPF gyro_z;
    SecondOrderLPF acc_x;
    SecondOrderLPF acc_y;
    SecondOrderLPF acc_z;

    Measurement_t* _meas_data;
    float _sample_hz;
    float _dt = 1.0f / _sample_hz;
    vec3_t _gyroPrev = {0.0, 0.0, 0.0};
    float ALPHA_ACC_LPF = (2.0f * PI * ACC_LPF_FREQ * DT) / (2.0f * PI * ACC_LPF_FREQ * DT + 1.0f);
    float ALPHA_GYRO_LPF = (2.0f * PI * GYRO_LPF_FREQ * DT) / (2.0f * PI * GYRO_LPF_FREQ * DT + 1.0f);
    float ALPHA_HPF = (1.0f / (2.0f * PI * GYRO_HPF_FREQ * DT + 1.0f));
    float ALPHA_MAG_LPF = (2.0f * PI * MAG_LPF_FREQ * DT) / (2.0f * PI * MAG_LPF_FREQ * DT + 1.0f);
};

#endif