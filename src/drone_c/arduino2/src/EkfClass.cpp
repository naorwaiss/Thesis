#include "EkfClass.h"

Measurement_t* EKF::meas = nullptr;
float delta_t = 0;

EKF::EKF(Measurement_t* meas_data, float dt) {
    meas = meas_data;
    R(2,2) *= 5.0;  // Higher noise for yaw measurement
    Q(3,3) *= 0.5;  // Lower process noise for quaternion z component
    delta_t = dt;
}

void EKF::pre_kalman_filter() {
    // Calculate pitch and roll from accelerometer
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
    float yaw = atan2(-by, bx);

    gyro_input(0) = meas->gyroRAD.x;
    gyro_input(1) = meas->gyroRAD.y;
    gyro_input(2) = meas->gyroRAD.z;

    // euler angle based on measurement
    euler_data(0) = roll;
    euler_data(1) = pitch;
    euler_data(2) = yaw;
}

// Proper EKF implementation with quaternions
attitude_t EKF::ekf_update(Vector3f gyro_sample, Vector3f euler_data) {
    float dt = 1.0f / SAMPLE_RATE;
    
    // Prediction Step
    // 1. State prediction using nonlinear quaternion propagation
    Vector4f q_pred = quaternion_propagate(state, gyro_sample, dt);
    normalize_quaternion(q_pred);
    
    // 2. Compute state transition Jacobian
    Matrix4f F = compute_state_jacobian(state, gyro_sample, dt);
    
    // 3. Predict error covariance
    P = F * P * F.transpose() + Q * dt;
    
    // Ensure P stays positive definite
    for(int i = 0; i < 4; i++) {
        if(P(i,i) < 1e-6f) P(i,i) = 1e-6f;
    }
    
    // Update Step
    // 4. Compute measurement Jacobian
    MatrixXf H = compute_measurement_jacobian(q_pred);
    
    // 5. Compute Kalman gain
    Matrix3f S = H * P * H.transpose() + R;
    
    // Check if S is invertible
    float det_S = S.determinant();
    if(abs(det_S) < 1e-9f) {
        // If S is nearly singular, skip update
        state = q_pred;
    } else {
        MatrixXf K = P * H.transpose() * S.inverse();
        
        // 6. Compute measurement prediction
        Vector3f euler_pred = quaternion_to_euler(q_pred);
        
        // 7. Compute measurement residual
        Vector3f measurement_error = euler_data - euler_pred;
        
        // Handle yaw discontinuity
        while (measurement_error(2) > PI) measurement_error(2) -= 2 * PI;
        while (measurement_error(2) < -PI) measurement_error(2) += 2 * PI;
        
        // 8. Update state
        Vector4f state_update = K * measurement_error;
        state = q_pred + state_update;
        normalize_quaternion(state);
        
        // 9. Update error covariance (Joseph form for better numerical stability)
        Matrix4f I_KH = I - K * H;
        P = I_KH * P * I_KH.transpose() + K * R * K.transpose();
        
        // Ensure P stays positive definite after update
        for(int i = 0; i < 4; i++) {
            if(P(i,i) < 1e-6f) P(i,i) = 1e-6f;
        }
    }
    
    // Prepare return data
    attitude_t return_data;
    Vector3f final_euler = quaternion_to_euler(state);
    return_data.roll = final_euler(0) * (180.0f / PI);
    return_data.pitch = final_euler(1) * (180.0f / PI) * -1;
    return_data.yaw = final_euler(2) * (180.0f / PI);
    
    return return_data;
}

// Nonlinear quaternion state propagation
Vector4f EKF::quaternion_propagate(Vector4f q, Vector3f gyro, float dt) {
    // Quaternion rate equation: dq/dt = 0.5 * Ω * q
    // where Ω is the skew-symmetric matrix of angular velocity
    
    float wx = gyro(0), wy = gyro(1), wz = gyro(2);
    
    // Skew-symmetric matrix Ω
    Matrix4f Omega;
    Omega << 0, -wx, -wy, -wz,
             wx,  0,  wz, -wy,
             wy, -wz,  0,  wx,
             wz,  wy, -wx,  0;
    
    // First-order integration
    Vector4f q_dot = 0.5f * Omega * q;
    Vector4f q_new = q + q_dot * dt;
    
    return q_new;
}

// Compute state transition Jacobian
Matrix4f EKF::compute_state_jacobian(Vector4f q, Vector3f gyro, float dt) {
    float wx = gyro(0), wy = gyro(1), wz = gyro(2);
    
    // Jacobian of quaternion rate equation with respect to quaternion
    Matrix4f F;
    F << 0, -wx, -wy, -wz,
         wx,  0,  wz, -wy,
         wy, -wz,  0,  wx,
         wz,  wy, -wx,  0;
    
    F = 0.5f * F * dt;
    F += Matrix4f::Identity();
    
    return F;
}

// Convert quaternion to Euler angles
Vector3f EKF::quaternion_to_euler(Vector4f q) {
    float qw = q(0), qx = q(1), qy = q(2), qz = q(3);
    
    // Roll (x-axis rotation)
    float sinr_cosp = 2.0f * (qw * qx + qy * qz);
    float cosr_cosp = 1.0f - 2.0f * (qx * qx + qy * qy);
    float roll = atan2(sinr_cosp, cosr_cosp);
    
    // Pitch (y-axis rotation)
    float sinp = 2.0f * (qw * qy - qz * qx);
    float pitch;
    if (abs(sinp) >= 1.0f) {
        pitch = copysign(PI / 2.0f, sinp); // Use 90 degrees if out of range
    } else {
        pitch = asin(sinp);
    }
    
    // Yaw (z-axis rotation)
    float siny_cosp = 2.0f * (qw * qz + qx * qy);
    float cosy_cosp = 1.0f - 2.0f * (qy * qy + qz * qz);
    float yaw = atan2(siny_cosp, cosy_cosp);
    
    return Vector3f(roll, pitch, yaw);
}

// Compute measurement Jacobian (derivative of Euler angles w.r.t. quaternion)
MatrixXf EKF::compute_measurement_jacobian(Vector4f q) {
    float qw = q(0), qx = q(1), qy = q(2), qz = q(3);
    
    // Jacobian matrix H (3x4): derivatives of [roll, pitch, yaw] w.r.t. [qw, qx, qy, qz]
    MatrixXf H(3, 4);
    
    // Simplified and more stable Jacobian computation
    // Roll derivatives
    float denom_roll = 1.0f - 2.0f * (qx * qx + qy * qy);
    if(abs(denom_roll) < 1e-6f) denom_roll = 1e-6f;
    
    H(0, 0) = 2.0f * qx / denom_roll;
    H(0, 1) = 2.0f * qw / denom_roll;
    H(0, 2) = 2.0f * qz / denom_roll;
    H(0, 3) = 2.0f * qy / denom_roll;
    
    // Pitch derivatives
    float denom_pitch = sqrt(1.0f - 4.0f * (qw * qy - qz * qx) * (qw * qy - qz * qx));
    if (denom_pitch < 1e-6f) denom_pitch = 1e-6f;
    
    H(1, 0) = 2.0f * qy / denom_pitch;
    H(1, 1) = -2.0f * qz / denom_pitch;
    H(1, 2) = 2.0f * qw / denom_pitch;
    H(1, 3) = -2.0f * qx / denom_pitch;
    
    // Yaw derivatives
    float denom_yaw = 1.0f - 2.0f * (qy * qy + qz * qz);
    if(abs(denom_yaw) < 1e-6f) denom_yaw = 1e-6f;
    
    H(2, 0) = 2.0f * qz / denom_yaw;
    H(2, 1) = 2.0f * qy / denom_yaw;
    H(2, 2) = 2.0f * qx / denom_yaw;
    H(2, 3) = 2.0f * qw / denom_yaw;
    
    return H;
}

// Normalize quaternion to unit length
void EKF::normalize_quaternion(Vector4f& q) {
    float norm = sqrt(q(0) * q(0) + q(1) * q(1) + q(2) * q(2) + q(3) * q(3));
    if (norm > 1e-6f) {
        q = q / norm;
    } else {
        q = Vector4f(1.0f, 0.0f, 0.0f, 0.0f);  // Identity quaternion
    }
}

void EKF::run_kalman(attitude_t* return_euiler, quat_t* return_quart) {
    // Detect vibrations and update motor state
    detectVibration();
    
    // Pre-process the data
    pre_kalman_filter();
    
    // Run the EKF
    Vector3f gyro_vec(gyro_input.x(), gyro_input.y(), gyro_input.z());
    *return_euiler = ekf_update(gyro_vec, euler_data);
    
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
    
    // Update Q matrix (process noise) - 4x4 for quaternions
    Q = Matrix4f::Identity() * (Q_total * q_multiplier);
    
    // Update R matrix (measurement noise) - 3x3 for Euler angles
    R = Matrix3f::Identity() * (R_total * r_multiplier);
}

float EKF::calculateVibrationLevel() {
    return motor_vibration_level;
}