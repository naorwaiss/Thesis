#ifndef EKFFILTER_H
#define EKFFILTER_H

#include <Arduino.h>
#include "Var_types.h"

class EKF {
   public:
    // Constructor: Takes a pointer to Measurement_t
    EKF(Measurement_t* meas);

    float state_vector[4];             // State vector: [Roll, Pitch, Yaw, Yaw Bias]
    float cov_matrix[4][4];            // Covariance matrix
    float process_nois_matrix[4][4];   // Process noise covariance matrix
    float measure_noise_matrix[3][3];  // Measurement noise covariance matrix

    void init_EKF();
    void predict(float dt);
    void update_measerment();
    attitude_s single_process_imu(long time);
    quat_t eulerToQuaternion(attitude_s *euiler);
    attitude_s lowPassFilter(attitude_s& input , attitude_s& filter_in);
    attitude_s highPassFilter(attitude_s& input, attitude_s& filter_in);
    void InitialFiltering(float DT);
   private:
    Measurement_t* measurement;  // Store the pointer to measurement
};

#endif
