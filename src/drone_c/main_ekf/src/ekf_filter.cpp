#include <Arduino.h>
#include "ekf_filter.h"
#include "Var_types.h"

EKF::EKF(Measurement_t* meas) : measurement(meas) {
    if (!measurement) {
        Serial.println("ERROR: Measurement pointer is NULL!");
    }
}



void kalman_filter(Measurement_t* meas, float dt) {



}





void kalman_1d(float KalmanState, float KalmanUncertainty, 
    float KalmanInput, float KalmanMeasurement)
{
// 1. State prediction via integration of gyro:
//    Angle_new = Angle_old + Ts * gyro_rate
float Ts = 0.004; // 250 Hz loop (example)
KalmanState = KalmanState + Ts * KalmanInput;

// 2. Uncertainty prediction:
//    Q ~ (gyro noise variance). Below: 4°/s is a typical guess => (4*Ts)^2
KalmanUncertainty = KalmanUncertainty + (Ts * Ts) * (4.0f * 4.0f);

// 3. Kalman Gain:
//    R ~ (accelerometer angle noise). Suppose 3° stdev => R=9
float MeasurementVariance = 3.0f * 3.0f; 
float KalmanGain = KalmanUncertainty / (KalmanUncertainty + MeasurementVariance);

// 4. State update with accelerometer measurement
KalmanState = KalmanState + KalmanGain * (KalmanMeasurement - KalmanState);

// 5. Uncertainty update
KalmanUncertainty = (1.0f - KalmanGain) * KalmanUncertainty;

// Return the results via global array or references
Kalman1DOutput[0] = KalmanState;
Kalman1DOutput[1] = KalmanUncertainty;
}