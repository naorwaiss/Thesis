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

// Base noise parameters (for stationary/motors off)
#define Q_const (0.07f * sqrt(400))   
#define R_const (0.00009f * sqrt(400)) 

// Motor noise multipliers
#define MOTOR_Q_MULTIPLIER 1.5f  // Increase process noise when motors are on
#define MOTOR_R_MULTIPLIER 5.0f  // Significantly increase measurement noise when motors are on

using Eigen::Matrix2f;
using Eigen::Matrix3f;
using Eigen::Vector2f;
using Eigen::Vector3f;

class EKF {
   private:
    static Measurement_t* meas;
    static const float dt;
    
    // Motor state tracking
    bool motors_active = false;
    float motor_vibration_level = 0.0f;
    float vibration_threshold = 0.1f;  // Threshold to detect motor vibrations
    
    // IMU data:
    float gyro_noise_density = 3.8e-3f * deg2rad;  // Gyro noise density in rad/(s*√Hz)
    float accel_noise_density = 70e-6f; // Accelerometer noise density in g/√Hz at ±2g
    float gyro_noise_var = pow((gyro_noise_density * sqrt(SAMPLE_RATE)), 2); // Gyro noise variance in rad^2
    float accel_noise_var = pow((accel_noise_density * sqrt(SAMPLE_RATE)),2); // Accelerometer noise variance in m/s^2
    
    // Base noise parameters
    float Q_integration_error = 10.0f;
    float Q_model_error = 5.0f;
    float Q_disturbance_error = 20.0f;
    float Q_unknown_error = 10.0f;
    float Q_sensor_error = gyro_noise_var * pow(DT,2);
    float Q_total = Q_sensor_error * Q_integration_error * Q_model_error * Q_disturbance_error * Q_unknown_error *100000;
    
    float R_external_accel_error = 1000.0f;
    float R_vibration_error = 50.0f;
    float R_nonlinear_error = 5.0f;
    float R_alignment_error = 2.0f;
    float R_temperature_error = 1.5f;
    float R_total = accel_noise_var * R_external_accel_error * R_vibration_error * R_nonlinear_error * R_alignment_error * R_temperature_error/200;

   public:
    Vector3f state = Vector3f::Zero();
    Matrix3f P = Matrix3f::Identity() * P_const;
    Matrix3f Q = Matrix3f::Identity() * Q_total;
    Matrix3f R = Matrix3f::Identity() * R_total;
    Matrix3f I = Matrix3f::Identity();
    Vector3f prev_gyro = Vector3f::Zero();
    Vector3f gyro_input;
    Vector3f euler_data;
    vec3_t gyroPrev = {0.0, 0.0, 0.0};

    explicit EKF(Measurement_t* meas_data, float dt);
    attitude_t kalman3D(Vector3f gyro, Vector3f euler_data);

    void pre_kalman_filter();
    void run_kalman(attitude_t* return_euiler, quat_t* return_quart);
    quat_t get_quart(attitude_t* euiler);
    
    // New methods for motor-aware filtering
    void updateMotorState(bool motors_on);
    void detectVibration();
    void adaptNoiseParameters();
    float calculateVibrationLevel();
};

#endif