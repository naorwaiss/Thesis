#include "EkfClass.h"

Measurement_t* EKF::meas = nullptr;
float delta_t = 0;

EKF::EKF(Measurement_t* meas_data, float dt) {
    meas = meas_data;
    delta_t = dt;
}


void EKF::pre_kalman_filter() {
    // InitialFiltering();

    // Calculate pitch and roll from accelerometer
    float pitch = atan2(meas->acc_LPF.y, sqrt(meas->acc_LPF.x * meas->acc_LPF.x + meas->acc_LPF.z * meas->acc_LPF.z));
    float roll = atan2(-meas->acc_LPF.x, meas->acc_LPF.z);

    // Improved tilt compensation for magnetometer
    float sin_roll = sin(roll);
    float cos_roll = cos(roll);
    float sin_pitch = sin(pitch);
    float cos_pitch = cos(pitch);

    // Tilt-compensated magnetic field components
    float bx = meas->mag.x * cos_pitch +
               meas->mag.y * sin_roll * sin_pitch +
               meas->mag.z * cos_roll * sin_pitch;

    float by = meas->mag.y * cos_roll -
               meas->mag.z * sin_roll;

    // Calculate yaw from compensated magnetometer data
    float yaw = atan2(-by, bx);  /// yaw mase on the mag read

    // Serial.println(yaw);

    gyro_input(0) = meas->gyro_LPF.x;
    gyro_input(1) = meas->gyro_LPF.y;
    gyro_input(2) = meas->gyro_LPF.z;

    // euler angle base on measerment
    euler_data(0) = roll;
    euler_data(1) = pitch;
    euler_data(2) = yaw;
}

// New 3D Kalman filter implementation
attitude_t EKF::kalman3D(Vector3f gyro_sample, Vector3f euler_data) {
    // Prediction step

    // Time update - integrate gyro rates with special handling for yaw
    // Vector3f angle_increment = 0.5f * (1.0f / SAMPLE_RATE) * (gyro + prev_gyro);
    Vector3f angle_increment = 0.5f * (1.0f / SAMPLE_RATE) * (gyro_sample - prev_gyro);

    // Update state with gyro data
    state(0) += angle_increment(0);  // Roll
    state(1) += angle_increment(1);  // Pitch
    state(2) += angle_increment(2);  // Yaw - direct integration of gyro Z

    prev_gyro = gyro_sample;

    // Update error covariance matrix
    // Make yaw component of Q higher to trust gyro more for yaw
    Matrix3f Q_adjusted = Q;
    Q_adjusted(2, 2) = Q_const * 1.5f;  // Increase process noise for yaw

    P = P + Q_adjusted * (1.0f / SAMPLE_RATE);

    // Measurement update
    // Make yaw component of R higher to trust magnetometer less
    Matrix3f R_adjusted = R;
    R_adjusted(2, 2) = R_const * 5.0f;  // Increase measurement noise for yaw

    Matrix3f S = P + R_adjusted;
    Matrix3f K = P * S.inverse();

    // Calculate yaw error, handling the 180/-180 discontinuity
    Vector3f measurement_error = euler_data - state;

    // Normalize yaw error to prevent issues at -π/π boundary
    // while (measurement_error(2) > PI) measurement_error(2) -= 2 * PI;
    // while (measurement_error(2) < -PI) measurement_error(2) += 2 * PI;

    // Correction step with special handling for yaw
    state += K * measurement_error;

    // Normalize angles
    while (state(2) > PI) state(2) -= 2 * PI;
    while (state(2) < -PI) state(2) += 2 * PI;

    // Update error covariance
    P = (I - K) * P;

    // Prepare return data
    attitude_t return_data;
    return_data.roll = state(1) * (180.0f / PI);
    return_data.pitch = state(0) * (180.0f / PI) * -1;
    return_data.yaw = state(2) * (180.0f / PI);

    return return_data;
}

void EKF::run_kalman(attitude_t* return_euiler, quat_t* return_quart) {
    pre_kalman_filter();
    // pre_kalman();
    *return_euiler = kalman3D(gyro_input, euler_data);
    *return_quart = get_quart(return_euiler);
}

// void EKF::InitialFiltering() {
//     // meas->acc_LPF.x = (1 - ALPHA_ACC_LPF) * meas->acc.x + ALPHA_ACC_LPF * meas->acc_LPF.x;
//     // meas->acc_LPF.y = (1 - ALPHA_ACC_LPF) * meas->acc.y + ALPHA_ACC_LPF * meas->acc_LPF.y;
//     // meas->acc_LPF.z = (1 - ALPHA_ACC_LPF) * meas->acc.z + ALPHA_ACC_LPF * meas->acc_LPF.z;

//     meas->acc_LPF.x = ALPHA_ACC_LPF * meas->acc.x + (1 - ALPHA_ACC_LPF) * meas->acc_LPF.x;
//     meas->acc_LPF.y = ALPHA_ACC_LPF * meas->acc.y + (1 - ALPHA_ACC_LPF) * meas->acc_LPF.y;
//     meas->acc_LPF.z = ALPHA_ACC_LPF * meas->acc.z + (1 - ALPHA_ACC_LPF) * meas->acc_LPF.z;

//     // Apply High-pass Filter to Gyro - > RAD. Used for the filter

//     meas->gyro_HPF.x = ALPHA_HPF * (meas->gyro_HPF.x + meas->gyroRAD.x - gyroPrev.x);
//     meas->gyro_HPF.y = ALPHA_HPF * (meas->gyro_HPF.y + meas->gyroRAD.y - gyroPrev.y);
//     meas->gyro_HPF.z = ALPHA_HPF * (meas->gyro_HPF.z + meas->gyroRAD.z - gyroPrev.z);

//     gyroPrev.x = meas->gyroRAD.x;
//     gyroPrev.y = meas->gyroRAD.y;
//     gyroPrev.z = meas->gyroRAD.z;

//     // Apply Low-pass Filter to Gyro - > DEG. Used for acro
//     meas->gyro_LPF.x = ALPHA_GYRO_LPF * meas->gyroDEG.x + (1 - ALPHA_GYRO_LPF) * meas->gyro_LPF.x;
//     meas->gyro_LPF.y = ALPHA_GYRO_LPF * meas->gyroDEG.y + (1 - ALPHA_GYRO_LPF) * meas->gyro_LPF.y;
//     meas->gyro_LPF.z = ALPHA_GYRO_LPF * meas->gyroDEG.z + (1 - ALPHA_GYRO_LPF) * meas->gyro_LPF.z;

//     // Apply Low-pass Filter to Mag
//     meas->mag_LPF.x = (1 - ALPHA_MAG_LPF) * meas->mag.x + ALPHA_MAG_LPF * meas->mag_LPF.x;
//     meas->mag_LPF.y = (1 - ALPHA_MAG_LPF) * meas->mag.y + ALPHA_MAG_LPF * meas->mag_LPF.y;
//     meas->mag_LPF.z = (1 - ALPHA_MAG_LPF) * meas->mag.z + ALPHA_MAG_LPF * meas->mag_LPF.z;
// }

quat_t EKF::get_quart(attitude_t* euiler) {
    quat_t q;

    float cy = cos(euiler->yaw * 0.5f);
    float sy = sin(euiler->yaw * 0.5f);
    float cp = cos(euiler->pitch * 0.5f);
    float sp = sin(euiler->pitch * 0.5f);
    float cr = cos(euiler->roll * 0.5f);
    float sr = sin(euiler->roll * 0.5f);

    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}