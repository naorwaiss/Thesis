#ifndef EKF_H
#define EKF_H

#include "Var_types.h"
#include "eigen.h"
#include <Eigen/LU>

/*
Tuning Strategy

Start conservative:

Small Q (trust gyro)
Large R (don't trust accel)


If output is too smooth/slow:

Increase Q slightly OR decrease R slightly


If output is too noisy:

Decrease Q OR increase R


For dynamic scenarios:

Increase R when accelerating (less trust in accel)
Decrease R when stationary (more trust in accel)



The key insight: Q and R work opposite to each other - when one goes up, the filter trusts the other source more!

First Test Strategy:

Try this configuration first - it should be much smoother than your current ±5° noise
If too slow/sluggish: Increase some of the Q factors by 10x
If still noisy: Increase some of the R factors by 10x
Monitor during different flight phases:

Hovering (should be smooth)
Gentle maneuvers (should track well)
Aggressive maneuvers (should not be corrupted by false accelerations)
*/



// The P matrix is how much we are confident in the filter in its current estimation.
// Higher P means we are less confident in the estimation  -> Rely more on the measurements  -> Greater K value.
// Lower P means we are more confident in the estimation  -> Rely more on the prediction  -> Smaller K
#define P_const 0.01f

// Bigger Q will result in less trust in the gyro. The prediction (model based) is noisy and less accurate.
// Smaller Q results in more trust in the gyro integration. The correction will affect less -> Smooth but slower.
// Its not just the gyro noise, but also model errors, like the error of the numerical integration.
#define Q_const (0.07f * sqrt(400))   
// Bigger R will result in less trust in the accelerometer. The measurements are noisy and less accurate.
//     Bigger R is good when the drone is accelerating because the accelerometer measures more forces than just gravity.
// Smaller R results in more trust in the accelerometer. The correction affects more. Good when the drone is not accelerating.
// Its not just the accelerometer noise, also the effectiveness of external forces, vibrations, approximation errors due to atan2.
#define R_const (0.00009f * sqrt(400)) 

using Eigen::Matrix2f;
using Eigen::Matrix3f;
using Eigen::Vector2f;
using Eigen::Vector3f;

class EKF {
   private:
    static Measurement_t* meas;
    static const float dt;
    // IMU data:
    float gyro_noise_density = 3.8e-3f * deg2rad;  // Gyro noise density in rad/(s*√Hz)
    float accel_noise_density = 70e-6f; // Accelerometer noise density in g/√Hz at ±2g
    float gyro_noise_var = pow((gyro_noise_density * sqrt(SAMPLE_RATE)), 2); // Gyro noise variance in rad^2
    float accel_noise_var = pow((accel_noise_density * sqrt(SAMPLE_RATE)),2); // Accelerometer noise variance in m/s^2
    // Other data that need to taken into account -- For Q:
    float Q_integration_error = 10.0f; // Integration error for Q matrix, adjust based on system dynamics
    float Q_model_error = 5.0f; // Error due to linearization errors
    float Q_disturbance_error = 20.0f; // Error due to vibrations and wind etc..
    float Q_unknown_error = 10.0f; // Error due to unknown disturbances
    float Q_sensor_error = gyro_noise_var * pow(DT,2); // Sensor noise error, adjust based on sensor characteristics
    float Q_total = Q_sensor_error * Q_integration_error * Q_model_error * Q_disturbance_error * Q_unknown_error *100000;
    float R_external_accel_error = 1000.0f;  // External accelerations (BIGGEST factor!)
    float R_vibration_error = 50.0f;         // Propeller vibrations
    float R_nonlinear_error = 5.0f;          // atan2() nonlinearity during motion
    float R_alignment_error = 2.0f;          // Sensor misalignment
    float R_temperature_error = 1.5f;        // Temperature effects
    float R_total = accel_noise_var * R_external_accel_error * R_vibration_error * R_nonlinear_error * R_alignment_error * R_temperature_error/200; // * 1.5;
    // Other data that need to taken into account -- For R:

   public:



    Vector3f state = Vector3f::Zero();            // Change from Vector2f to Vector3f
    Matrix3f P = Matrix3f::Identity() * P_const;  // Change all matrices to 3x3
    Matrix3f Q = Matrix3f::Identity() * Q_total; // Process noise covariance matrix
    Matrix3f R = Matrix3f::Identity() * R_total; // Measurement noise covariance matrix
    Matrix3f I = Matrix3f::Identity();
    Vector3f prev_gyro = Vector3f::Zero();
    Vector3f gyro_input;  // Include z-axis gyro
    Vector3f euler_data;  // Include yaw measurements
    vec3_t gyroPrev = {0.0, 0.0, 0.0};

    explicit EKF(Measurement_t* meas_data, float dt);
    attitude_t kalman3D(Vector3f gyro, Vector3f euler_data);

    void pre_kalman();
    void pre_kalman_filter();
    void run_kalman(attitude_t* return_euiler, quat_t* return_quart);
    quat_t get_quart(attitude_t* euiler);
};

#endif