#ifndef EKF_H
#define EKF_H

#include "Var_types.h"
#include "eigen.h"
#include <Eigen/LU>

// #define P_const 0.0008f
#define P_const 10.0f

#define Q_const (0.07f * sqrt(400))
#define R_const (0.00009f * sqrt(400))

using Eigen::Matrix2f;
using Eigen::Matrix3f;
using Eigen::Vector2f;
using Eigen::Vector3f;

class EKF {
   private:
    static Measurement_t* meas;
    static const float dt;

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
};

#endif