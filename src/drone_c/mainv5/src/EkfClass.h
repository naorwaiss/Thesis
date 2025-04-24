#ifndef EKF_H
#define EKF_H

#include "Var_types.h"
#include "eigen.h"
#include <Eigen/LU>

// #define P_const 0.0008f
#define P_const 0.01f

#define Q_const (0.07f * sqrt(400))
#define R_const (0.00009f * sqrt(400))

using Eigen::Matrix2f;
using Eigen::Matrix3f;
using Eigen::Vector2f;
using Eigen::Vector3f;

// Filter Frequencies:
#define ACC_LPF_FREQ 40.0f   // Increase from 10.0f
// #define ACC_LPF_FREQ 1000.0f   // Increase from 10.0f
#define GYRO_LPF_FREQ 40.0f  // Increase from 40.0f
#define GYRO_HPF_FREQ 0.5f   // Lower from 2.5f to reduce drift removal aggressiveness
#define MAG_LPF_FREQ 15.0f   // Increase from 10.0f

// static const float ALPHA_ACC_LPF = (2.0f * PI * ACC_LPF_FREQ * DT / (2.0f * PI * ACC_LPF_FREQ * DT + 1.0f));
// static const float ALPHA_GYRO_LPF = (2.0f * PI * GYRO_LPF_FREQ * DT / (2.0f * PI * GYRO_LPF_FREQ * DT + 1.0f));
// static const float ALPHA_HPF = (1.0f / (2.0f * PI * GYRO_HPF_FREQ * DT + 1.0f));
// static const float ALPHA_MAG_LPF = (2.0f * PI * MAG_LPF_FREQ * DT / (2.0f * PI * MAG_LPF_FREQ * DT + 1.0f));

class EKF {
   private:
    static Measurement_t* meas;
    static const float dt;
    // extern Eigen::Matrix2f;
    // extern Eigen::Vector2f;

   public:
    Vector3f state = Vector3f::Zero();            // Change from Vector2f to Vector3f
    Matrix3f P = Matrix3f::Identity() * P_const;  // Change all matrices to 3x3
    Matrix3f Q = Matrix3f::Identity() * Q_const;
    Matrix3f R = Matrix3f::Identity() * R_const;
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

    // void InitialFiltering();
};

#endif