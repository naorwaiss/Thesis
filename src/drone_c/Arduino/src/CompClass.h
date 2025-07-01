#ifndef COMPCLASS_H
#define COMPCLASS_H

#include <Arduino.h>
#include "Var_types.h"




// Angle conversion constants:

// Motion thresholds and filter parameters
// #define LOW_MOTION 0.2f
// #define HIGH_MOTION 1.5f
#define LOW_MOTION 0.15f * 9.81   // Slightly lower than 0.2f
#define HIGH_MOTION 1.2f * 9.81    // Lower than 1.5f to activate high correction sooner

#define HIGH_BETA 0.9f // Rely more on accelerometer
#define LOW_BETA 0.3f // Rely more on gyroscope
#define DEFAULT_BETA 0.8f   

// Filter Frequencies:
// #define ACC_LPF_FREQ 80.0f   // Increase from 10.0f
// // #define ACC_LPF_FREQ 1000.0f   // Increase from 10.0f
// #define GYRO_LPF_FREQ 80.0f  // Increase from 40.0f
// #define GYRO_HPF_FREQ 1.0f   // Lower from 2.5f to reduce drift removal aggressiveness
// #define MAG_LPF_FREQ 50.0f   // Increase from 10.0f

// Calculate filter coefficients based on cutoff frequencies
// static const float SAMPLE_RATE = 1100.0f;
// static const float DT = 1.0f/SAMPLE_RATE;
// static const float ALPHA_ACC_LPF = (2.0f * PI * ACC_LPF_FREQ * DT) / (2.0f * PI * ACC_LPF_FREQ * DT + 1.0f);
// static const float ALPHA_GYRO_LPF = (2.0f * PI * GYRO_LPF_FREQ * DT) / (2.0f * PI * GYRO_LPF_FREQ * DT + 1.0f);
// static const float ALPHA_HPF = (1.0f / (2.0f * PI * GYRO_HPF_FREQ * DT + 1.0f));
// static const float ALPHA_MAG_LPF = (2.0f * PI * MAG_LPF_FREQ * DT) / (2.0f * PI * MAG_LPF_FREQ * DT + 1.0f);


class CompFilter {
    public:
        CompFilter(bool _MAG = 1) : USE_MAG(_MAG) {}
        bool USE_MAG;


        quat_t q = {0.0, 0.0, 0.0, 1.0};
        quat_t qDot_prev ={0.0, 0.0, 0.0, 0.0};
        // Params for HPF and LPF:
        vec3_t accFiltered = {0.0, 0.0, 0.0};
        vec3_t gyroFiltered = {0.0, 0.0, 0.0};
        vec3_t magFiltered = {0.0, 0.0, 0.0};
        float accNorm = 0.0;
        float drift = 0.0;
        float driftRate = 0.005;
        float gravX , gravY, gravZ; // Unit vector in the direction of the estimated gravity
        vec3_t gyroPrev = {0.0, 0.0, 0.0};



        void UpdateQ(Measurement_t* , float );
        // void InitialFiltering(Measurement_t* );
        float calculateDynamicBeta(Measurement_t );
        float invSqrt(float x);
        void GetQuaternion(quat_t* q_);
        void GetEulerRPYrad(attitude_s* , float);
        void GetEulerRPYdeg(attitude_s* , float);
        void estimatedGravityDir(float* , float* , float*);
        float GetAccZ(float , float , float );
};

#endif