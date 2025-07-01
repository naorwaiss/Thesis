#include "EkfClass.h"

Measurement_t* EKF::meas = nullptr;
float delta_t = 0;

EKF::EKF(Measurement_t* meas_data, float dt) {
    meas = meas_data;
    R(2,2) *= 5.0;
    Q(2,2) *= 0.5;
    delta_t = dt;
}

void EKF::pre_kalman_filter() {
    // InitialFiltering();

    // Calculate pitch and roll from accelerometer
    // float pitch = atan2(meas->acc_LPF.y, sqrt(meas->acc_LPF.x * meas->acc_LPF.x + meas->acc_LPF.z * meas->acc_LPF.z));
    // float roll = atan2(-meas->acc_LPF.x, meas->acc_LPF.z);
    float pitch = atan2(meas->acc.y, sqrt(meas->acc.x * meas->acc.x + meas->acc.z * meas->acc.z));
    float roll = atan2(-meas->acc.x, meas->acc.z);

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

    gyro_input(0) = meas->gyroRAD.x;
    gyro_input(1) = meas->gyroRAD.y;
    gyro_input(2) = meas->gyroRAD.z;

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
    Vector3f angle_increment = (1.0f / SAMPLE_RATE) * gyro_sample;

    // Update state with gyro data
    state(0) += angle_increment(0);  // Roll
    state(1) += angle_increment(1);  // Pitch
    state(2) += angle_increment(2);  // Yaw - direct integration of gyro Z

    prev_gyro = gyro_sample;

    // Update error covariance matrix
    // Make yaw component of Q higher to trust gyro more for yaw

    P = P + Q * (1.0f / SAMPLE_RATE);
    Matrix3f S = P + R;
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
    return_data.roll = state(0) * (180.0f / PI);
    return_data.pitch = state(1) * (180.0f / PI) * -1;
    return_data.yaw = state(2) * (180.0f / PI);

    return return_data;
}

void EKF::run_kalman(attitude_t* return_euiler, quat_t* return_quart) {
    // Detect vibrations and update motor state
    detectVibration();
    
    // Pre-process the data
    pre_kalman_filter();
    
    // Run the Kalman filter
    Vector3f gyro_vec(gyro_input.x(), gyro_input.y(), gyro_input.z());
    *return_euiler = kalman3D(gyro_vec, euler_data);
    
    // Convert to quaternion
    *return_quart = get_quart(return_euiler);
}

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

void EKF::updateMotorState(bool motors_on) {
    motors_active = motors_on;
    adaptNoiseParameters();
}

void EKF::detectVibration() {
    // Calculate vibration level from accelerometer data
    float acc_magnitude = sqrt(meas->acc.x * meas->acc.x + meas->acc.y * meas->acc.y + meas->acc.z * meas->acc.z);
    float expected_gravity = 9.81f;
    float vibration = abs(acc_magnitude - expected_gravity);
    
    // Low-pass filter the vibration level
    motor_vibration_level = 0.9f * motor_vibration_level + 0.1f * vibration;
    
    // Update motor state based on vibration
    bool detected_motors = motor_vibration_level > vibration_threshold;
    if (detected_motors != motors_active) {
        updateMotorState(detected_motors);
    }
}

void EKF::adaptNoiseParameters() {
    float q_multiplier = motors_active ? MOTOR_Q_MULTIPLIER : 1.0f;
    float r_multiplier = motors_active ? MOTOR_R_MULTIPLIER : 1.0f;
    
    // Add additional vibration-based scaling
    if (motors_active) {
        float vibration_scale = 1.0f + (motor_vibration_level / vibration_threshold) * 2.0f;
        r_multiplier *= vibration_scale;
    }
    // Update Q matrix (process noise)
    Q = Matrix3f::Identity() * (Q_total * q_multiplier);
    
    // Update R matrix (measurement noise)
    R = Matrix3f::Identity() * (R_total * r_multiplier);
}

float EKF::calculateVibrationLevel() {
    return motor_vibration_level;
}