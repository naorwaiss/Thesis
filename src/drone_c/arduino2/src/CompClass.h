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