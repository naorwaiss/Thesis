#ifndef EKF_H
#define EKF_H

#include "Var_types.h"
#include "eigen.h"
#include <Eigen/LU>



#define P_const 0.001f
#define Q_const (0.07f * sqrt(400))
#define R_const (0.00009f * sqrt(400))

using Eigen::Matrix2f;
using Eigen::Vector2f;



// Filter Frequencies:
#define ACC_LPF_FREQ 40.0f   // Increase from 10.0f
#define GYRO_LPF_FREQ 40.0f  // Increase from 40.0f
#define GYRO_HPF_FREQ 0.5f   // Lower from 2.5f to reduce drift removal aggressiveness
#define MAG_LPF_FREQ 15.0f   // Increase from 10.0f

static const float ALPHA_ACC_LPF = (2.0f * PI * ACC_LPF_FREQ * DT / (2.0f * PI * ACC_LPF_FREQ * DT + 1.0f));
static const float ALPHA_GYRO_LPF = (2.0f * PI * GYRO_LPF_FREQ * DT / (2.0f * PI * GYRO_LPF_FREQ * DT + 1.0f));
static const float ALPHA_HPF = (1.0f / (2.0f * PI * GYRO_HPF_FREQ * DT + 1.0f));
static const float ALPHA_MAG_LPF = (2.0f * PI * MAG_LPF_FREQ * DT / (2.0f * PI * MAG_LPF_FREQ * DT + 1.0f));


class EKF {

   private:
    static Measurement_t* meas;
    static const float dt;
    // extern Eigen::Matrix2f;
    // extern Eigen::Vector2f;

   public:
    Vector2f state = Vector2f::Zero();
    Matrix2f P = Matrix2f::Identity() * P_const;
    Matrix2f Q = Matrix2f::Identity() * Q_const;
    Matrix2f R = Matrix2f::Identity() * R_const;
    Matrix2f I = Matrix2f::Identity();
    Vector2f prev_gyro = Vector2f::Zero();
    Vector2f gyro_input;
    Vector2f euiler_data;
    vec3_t gyroPrev = {0.0, 0.0, 0.0};
    explicit EKF(Measurement_t* meas, const float dt);
    attitude_t kalman2D(Vector2f gyro, Vector2f meas);
    void pre_kalman();
    void run_kalman(attitude_t* return_value);
    void get_quart();
    void mag_yaw();

    void InitialFiltering();    


};

#endif