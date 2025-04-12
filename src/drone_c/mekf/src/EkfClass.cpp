#include "EkfClass.h"

Measurement_t* EKF::meas = nullptr;
float delta_t = 0;

EKF::EKF(Measurement_t* meas_data, float dt) {
    meas = meas_data;
    delta_t = dt;
}

void EKF::pre_kalman() {
    float pitch = atan2(meas->acc.y, sqrt(meas->acc.x * meas->acc.x + meas->acc.z * meas->acc.z));
    float roll = atan2(-meas->acc.x, meas->acc.z);
    gyro_input(0) = meas->gyroDEG.x;
    gyro_input(1) = meas->gyroDEG.y;
    euiler_data(0) = pitch;
    euiler_data(1) = roll;
}

attitude_t EKF::kalman2D(Vector2f gyro, Vector2f euiler_data) {
    // Optional: use estimated yaw from another filter; set to zero for now
    float estimated_yaw = 0.0f;

    float cos_yaw = cos(estimated_yaw);
    float sin_yaw = sin(estimated_yaw);

    // Rotate gyro into fixed frame to avoid roll-pitch cross-contamination
    float gx_fixed = gyro(0) * cos_yaw - gyro(1) * sin_yaw;
    float gy_fixed = gyro(0) * sin_yaw + gyro(1) * cos_yaw;
    Vector2f gyro_fixed(gx_fixed, gy_fixed);

    state += 0.5f * (1 / SAMPLE_RATE) * (gyro_fixed + prev_gyro);
    prev_gyro = gyro_fixed;

    P = P + Q * (1 / SAMPLE_RATE);

    Matrix2f S = P + R;
    Matrix2f K = P * S.inverse();

    // Correction
    state += K * (euiler_data - state);
    P = (I - K) * P;
    attitude_t return_data;
    return_data.pitch = state(0);
    return_data.roll = state(1);
    return_data.yaw = 0.0f;
    return return_data;

}

void EKF::run_kalman(attitude_t* return_value) {
    pre_kalman();
    *return_value = kalman2D(gyro_input, euiler_data);
}



void EKF::InitialFiltering() {
    // meas->acc_LPF.x = (1 - ALPHA_ACC_LPF) * meas->acc.x + ALPHA_ACC_LPF * meas->acc_LPF.x;
    // meas->acc_LPF.y = (1 - ALPHA_ACC_LPF) * meas->acc.y + ALPHA_ACC_LPF * meas->acc_LPF.y;
    // meas->acc_LPF.z = (1 - ALPHA_ACC_LPF) * meas->acc.z + ALPHA_ACC_LPF * meas->acc_LPF.z;

    meas->acc_LPF.x = ALPHA_ACC_LPF * meas->acc.x + (1 - ALPHA_ACC_LPF) * meas->acc_LPF.x;
    meas->acc_LPF.y = ALPHA_ACC_LPF * meas->acc.y + (1 - ALPHA_ACC_LPF) * meas->acc_LPF.y;
    meas->acc_LPF.z = ALPHA_ACC_LPF * meas->acc.z + (1 - ALPHA_ACC_LPF) * meas->acc_LPF.z;

    // Apply High-pass Filter to Gyro - > RAD. Used for the filter

    meas->gyro_HPF.x = ALPHA_HPF * (meas->gyro_HPF.x + meas->gyroRAD.x - gyroPrev.x);
    meas->gyro_HPF.y = ALPHA_HPF * (meas->gyro_HPF.y + meas->gyroRAD.y - gyroPrev.y);
    meas->gyro_HPF.z = ALPHA_HPF * (meas->gyro_HPF.z + meas->gyroRAD.z - gyroPrev.z);

    gyroPrev.x = meas->gyroRAD.x;
    gyroPrev.y = meas->gyroRAD.y;
    gyroPrev.z = meas->gyroRAD.z;

    // Apply Low-pass Filter to Gyro - > DEG. Used for acro
    meas->gyro_LPF.x = ALPHA_GYRO_LPF * meas->gyroDEG.x + (1 - ALPHA_GYRO_LPF) * meas->gyro_LPF.x;
    meas->gyro_LPF.y = ALPHA_GYRO_LPF * meas->gyroDEG.y + (1 - ALPHA_GYRO_LPF) * meas->gyro_LPF.y;
    meas->gyro_LPF.z = ALPHA_GYRO_LPF * meas->gyroDEG.z + (1 - ALPHA_GYRO_LPF) * meas->gyro_LPF.z;

    // if (USE_MAG) {
    //     // Apply Low-pass Filter to Mag
    //     meas->mag_LPF.x = (1 - ALPHA_MAG_LPF) * meas->mag.x + ALPHA_MAG_LPF * meas->mag_LPF.x;
    //     meas->mag_LPF.y = (1 - ALPHA_MAG_LPF) * meas->mag.y + ALPHA_MAG_LPF * meas->mag_LPF.y;
    //     meas->mag_LPF.z = (1 - ALPHA_MAG_LPF) * meas->mag.z + ALPHA_MAG_LPF * meas->mag_LPF.z;
    
}