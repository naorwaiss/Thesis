#ifndef EKF_H
#define EKF_H

#include "Var_types.h"
#include "eigen.h"
#include <Eigen/LU>

/*
Extended Kalman Filter (EKF) for Attitude Estimation

This is a proper EKF implementation using:
- Quaternions as state vector (4D)
- Nonlinear state transition model
- Nonlinear measurement model  
- Proper Jacobian matrices
- Motor-aware adaptive noise parameters

State Vector: [q_w, q_x, q_y, q_z] (quaternion)
Measurement: [roll, pitch, yaw] from accelerometer + magnetometer
*/

// The P matrix is how much we are confident in the filter in its current estimation.
// Higher P means we are less confident in the estimation  -> Rely more on the measurements  -> Greater K value.
// Lower P means we are more confident in the estimation  -> Rely more on the prediction  -> Smaller K
#define P_const 0.1f  // Increased for more conservative initial uncertainty

// Base noise parameters (for stationary/motors off) - More conservative values
#define Q_const (0.01f * sqrt(400))   // Reduced process noise
#define R_const (0.001f * sqrt(400))  // Reduced measurement noise

// Motor noise multipliers - More conservative
#define MOTOR_Q_MULTIPLIER 1.2f  // Smaller increase in process noise when motors are on
#define MOTOR_R_MULTIPLIER 3.0f  // Reduced increase in measurement noise when motors are on

using Eigen::Matrix4f;
using Eigen::Matrix3f;
using Eigen::MatrixXf;
using Eigen::Vector4f;
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
    
    // Base noise parameters - More conservative values
    float Q_integration_error = 1.0f;      // Reduced from 10.0f
    float Q_model_error = 0.5f;            // Reduced from 5.0f
    float Q_disturbance_error = 2.0f;      // Reduced from 20.0f
    float Q_unknown_error = 1.0f;          // Reduced from 10.0f
    float Q_sensor_error = gyro_noise_var * pow(DT,2);
    float Q_total = Q_sensor_error * Q_integration_error * Q_model_error * Q_disturbance_error * Q_unknown_error ;
    
    float R_external_accel_error = 100.0f;  // Reduced from 1000.0f
    float R_vibration_error = 10.0f;        // Reduced from 50.0f
    float R_nonlinear_error = 1.0f;         // Reduced from 5.0f
    float R_alignment_error = 0.5f;         // Reduced from 2.0f
    float R_temperature_error = 0.3f;       // Reduced from 1.5f
    float R_total = accel_noise_var * R_external_accel_error * R_vibration_error * R_nonlinear_error * R_alignment_error * R_temperature_error;

   public:
    // State vector: quaternion [w, x, y, z]
    Vector4f state = Vector4f(1.0f, 0.0f, 0.0f, 0.0f);  // Identity quaternion
    
    // Covariance matrices
    Matrix4f P = Matrix4f::Identity() * P_const;  // State covariance (4x4)
    Matrix4f Q = Matrix4f::Identity() * Q_total;  // Process noise (4x4)
    Matrix3f R = Matrix3f::Identity() * R_total;  // Measurement noise (3x3)
    Matrix4f I = Matrix4f::Identity();
    
    // Previous gyro for integration
    Vector3f prev_gyro = Vector3f::Zero();
    Vector3f gyro_input;
    Vector3f euler_data;
    vec3_t gyroPrev = {0.0, 0.0, 0.0};

    explicit EKF(Measurement_t* meas_data, float dt);
    attitude_t ekf_update(Vector3f gyro, Vector3f euler_data);

    void pre_kalman_filter();
    void run_kalman(attitude_t* return_euiler, quat_t* return_quart);
    quat_t get_quart(attitude_t* euiler);
    
    // EKF-specific methods
    Vector4f quaternion_propagate(Vector4f q, Vector3f gyro, float dt);
    Matrix4f compute_state_jacobian(Vector4f q, Vector3f gyro, float dt);
    Vector3f quaternion_to_euler(Vector4f q);
    MatrixXf compute_measurement_jacobian(Vector4f q);
    void normalize_quaternion(Vector4f& q);
    
    // Motor-aware methods
    void updateMotorState(bool motors_on);
    void detectVibration();
    void adaptNoiseParameters();
    float calculateVibrationLevel();
};

#endif