#include <Arduino.h>
#include "ekf_filter.h"
#include "Var_types.h"

EKF::EKF(Measurement_t* meas) : measurement(meas) {
    if (!measurement) {
        Serial.println("ERROR: Measurement pointer is NULL!");
    }
}

void EKF::init_EKF() {
    state_vector[0] = state_vector[1] = state_vector[2] = state_vector[3] = 0;  // Roll, Pitch, Yaw, Yaw Bias

    // Initialize covariance and process noise matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cov_matrix[i][j] = (i == j) ? 1.0f : 0.0f;
            process_nois_matrix[i][j] = (i == j) ? 0.01f : 0.0f;
        }
    }

    // Ensure measurement is not null before accessing it
    if (measurement) {
        // Initialize measurement noise matrix with zeros first
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                measure_noise_matrix[i][j] = 0.0f;
            }
        }

        // Assign diagonal elements
        measure_noise_matrix[0][0] = 0.03 + measurement->acc_bias.x;   // Roll noise
        measure_noise_matrix[1][1] = 0.03f + measurement->acc_bias.y;  // Pitch noise
        measure_noise_matrix[2][2] = 0.1 + measurement->acc_bias.z;    // Yaw noise
    } else {
        Serial.println("Error: measurement pointer is NULL!");
    }
}

void EKF::predict(float dt) {
    // State transition: Predict next state using gyroscope
    state_vector[0] += dt * measurement->gyro_LPF.x;    // Roll
    state_vector[1] += dt * measurement->gyro_LPF.y;    // Pitch
    state_vector[2] += dt * (measurement->gyro_LPF.z);  // Yaw minus bias

    // Update state covariance: P = F * P * F^T + Q
    float F[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, -dt},
        {0, 0, 0, 1}};

    float cov_matrix_new[4][4] = {0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cov_matrix_new[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                cov_matrix_new[i][j] += F[i][k] * cov_matrix[k][j];
            }
            cov_matrix_new[i][j] += process_nois_matrix[i][j];  // Add process noise
        }
    }

    // Copy back updated covariance
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cov_matrix[i][j] = cov_matrix_new[i][j];
        }
    }
}

void EKF::update_measerment() {
    // Compute roll & pitch from accelerometer
    float roll_acc = atan2f(measurement->acc.y, measurement->acc.z) * 180.0f / PI;
    float pitch_acc = atan2f(-measurement->acc.x, sqrtf(measurement->acc.y * measurement->acc.y + measurement->acc.z * measurement->acc.z)) * 180.0f / PI;

    // Compute yaw from magnetometer
    float yaw_mag = atan2f(measurement->mag_LPF.y, measurement->mag_LPF.x) * 180.0f / PI;

    float z[3] = {roll_acc, pitch_acc, yaw_mag};
    float H[3][4] = {
        {1, 0, 0, 0},  // Roll measurement matrix
        {0, 1, 0, 0},  // Pitch measurement matrix
        {0, 0, 1, 0}   // Yaw measurement matrix
    };

    // Innovation: y = z - H*x
    float y[3] = {0};
    for (int i = 0; i < 3; i++) {
        y[i] = z[i];
        for (int j = 0; j < 4; j++) {
            y[i] -= H[i][j] * state_vector[j];
        }
    }

    // Compute Kalman gain: K = P * H^T * (H * P * H^T + R)^-1
    float S[3][3] = {0}, K[4][3] = {0};

    // Compute S = H * P * H^T + R
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            S[i][j] = measure_noise_matrix[i][j];
            for (int k = 0; k < 4; k++) {
                S[i][j] += H[i][k] * cov_matrix[k][j];
            }
        }
    }

    // Compute K = P * H^T * S^-1 (Assume diagonal R for simplicity)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            K[i][j] = cov_matrix[i][j] / S[j][j];
        }
    }

    // State update: x = x + K*y
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            state_vector[i] += K[i][j] * y[j];
        }
    }
}

attitude_s EKF::single_process_imu(long time) {
    attitude_s ati;
    double dt = (time / 1000000.0);
    InitialFiltering(dt);
    predict(dt);
    update_measerment();
    ati.roll = state_vector[0];
    ati.pitch = -1 * state_vector[1];
    ati.yaw = state_vector[2];
    return ati;
}

quat_t EKF::eulerToQuaternion(attitude_s* euiler) {
    // Convert degrees to radians from the ekf

    attitude_s euiler_modifide;
    quat_t quartirion;
    euiler_modifide.roll = euiler->roll * PI / 180.0f;
    euiler_modifide.pitch = euiler->pitch * PI / 180.0f;
    euiler_modifide.yaw = euiler->yaw * PI / 180.0f;

    // Compute half angles
    float cr = cos(euiler_modifide.roll * 0.5f);
    float sr = sin(euiler_modifide.roll * 0.5f);
    float cp = cos(euiler_modifide.pitch * 0.5f);
    float sp = sin(euiler_modifide.pitch * 0.5f);
    float cy = cos(euiler_modifide.yaw * 0.5f);
    float sy = sin(euiler_modifide.yaw * 0.5f);

    quartirion.w = cr * cp * cy + sr * sp * sy;
    quartirion.x = sr * cp * cy - cr * sp * sy;
    quartirion.y = cr * sp * cy + sr * cp * sy;
    quartirion.z = cr * cp * sy - sr * sp * cy;

    return quartirion;
}

#define ALPHA 0.2

attitude_s EKF::lowPassFilter(attitude_s& input, attitude_s& filter_in) {
    attitude_s filter_out;
    filter_out.roll = ALPHA * input.roll + (1 - ALPHA) * filter_in.roll;
    filter_out.pitch = ALPHA * input.pitch + (1 - ALPHA) * filter_in.pitch;
    filter_out.yaw = ALPHA * input.yaw + (1 - ALPHA) * filter_in.yaw;
    return filter_out;
}

attitude_s EKF::highPassFilter(attitude_s& input, attitude_s& filter_in) {
    attitude_s filter_out;
    filter_out.roll = (1 - ALPHA) * (filter_in.roll + input.roll - filter_in.roll);
    filter_out.pitch = (1 - ALPHA) * (filter_in.pitch + input.pitch - filter_in.pitch);
    filter_out.yaw = (1 - ALPHA) * (filter_in.yaw + input.yaw - filter_in.yaw);
    return filter_out;
}

#define ACC_LPF_FREQ 10.0f   // 10 Hz cutoff for accelerometer
#define GYRO_LPF_FREQ 50.0f  // 50 Hz cutoff for gyro
#define GYRO_HPF_FREQ 2.5f   // 0.1 Hz cutoff for gyro drift removal
#define MAG_LPF_FREQ 10.0f   // 10 Hz cutoff for magnetometer

// void EKF::InitialFiltering(float DT) {
//     float ALPHA_ACC_LPF = (2.0f * PI * ACC_LPF_FREQ * DT / (2.0f * PI * ACC_LPF_FREQ * DT + 1.0f));
//     float ALPHA_GYRO_LPF = (2.0f * PI * GYRO_LPF_FREQ * DT / (2.0f * PI * GYRO_LPF_FREQ * DT + 1.0f));
//     float ALPHA_HPF = (1.0f / (2.0f * PI * GYRO_HPF_FREQ * DT + 1.0f));
//     float ALPHA_MAG_LPF = (2.0f * PI * MAG_LPF_FREQ * DT / (2.0f * PI * MAG_LPF_FREQ * DT + 1.0f));

//     measurement->acc_LPF.x = (1 - ALPHA_ACC_LPF) * measurement->acc_LPF.x + ALPHA_ACC_LPF * measurement->acc.x;
//     measurement->acc_LPF.y = (1 - ALPHA_ACC_LPF) * measurement->acc_LPF.y + ALPHA_ACC_LPF * measurement->acc.y;
//     measurement->acc_LPF.z = (1 - ALPHA_ACC_LPF) * measurement->acc_LPF.z + ALPHA_ACC_LPF * measurement->acc.z;

//     static vec3_t gyroPrev = {0.0, 0.0, 0.0};
//     measurement->gyro_HPF.x = ALPHA_HPF * (measurement->gyro_HPF.x + measurement->gyro.x - gyroPrev.x);
//     measurement->gyro_HPF.y = ALPHA_HPF * (measurement->gyro_HPF.y + measurement->gyro.y - gyroPrev.y);
//     measurement->gyro_HPF.z = ALPHA_HPF * (measurement->gyro_HPF.z + measurement->gyro.z - gyroPrev.z);
//     gyroPrev.x = measurement->gyro.x;
//     gyroPrev.y = measurement->gyro.y;
//     gyroPrev.z = measurement->gyro.z;

//     measurement->gyro_LPF.x = (1 - ALPHA_GYRO_LPF) * measurement->gyro_LPF.x + ALPHA_GYRO_LPF * measurement->gyro.x;
//     measurement->gyro_LPF.y = (1 - ALPHA_GYRO_LPF) * measurement->gyro_LPF.y + ALPHA_GYRO_LPF * measurement->gyro.y;
//     measurement->gyro_LPF.z = (1 - ALPHA_GYRO_LPF) * measurement->gyro_LPF.z + ALPHA_GYRO_LPF * measurement->gyro.z;

//     measurement->mag_LPF.x = (1 - ALPHA_MAG_LPF) * measurement->mag_LPF.x + ALPHA_MAG_LPF * measurement->mag.x;
//     measurement->mag_LPF.y = (1 - ALPHA_MAG_LPF) * measurement->mag_LPF.y + ALPHA_MAG_LPF * measurement->mag.y;
//     measurement->mag_LPF.z = (1 - ALPHA_MAG_LPF) * measurement->mag_LPF.z + ALPHA_MAG_LPF * measurement->mag.z;

// }


void EKF::InitialFiltering(float DT) {
    float ALPHA_ACC_LPF = (2.0f * PI * ACC_LPF_FREQ * DT / (2.0f * PI * ACC_LPF_FREQ * DT + 1.0f));
    float ALPHA_GYRO_LPF = (2.0f * PI * GYRO_LPF_FREQ * DT / (2.0f * PI * GYRO_LPF_FREQ * DT + 1.0f));
    float ALPHA_HPF = (1.0f / (2.0f * PI * GYRO_HPF_FREQ * DT + 1.0f));
    float ALPHA_MAG_LPF = (2.0f * PI * MAG_LPF_FREQ * DT / (2.0f * PI * MAG_LPF_FREQ * DT + 1.0f));

    static vec3_t accPrev = {0.0, 0.0, 0.0};
    static vec3_t gyroPrev = {0.0, 0.0, 0.0};
    static vec3_t magPrev = {0.0, 0.0, 0.0};

    // Compute Gradient (Difference Between Current and Previous Measurement)
    vec3_t accGrad = {
        fabs(measurement->acc.x - accPrev.x),
        fabs(measurement->acc.y - accPrev.y),
        fabs(measurement->acc.z - accPrev.z)
    };

    vec3_t gyroGrad = {
        fabs(measurement->gyro.x - gyroPrev.x),
        fabs(measurement->gyro.y - gyroPrev.y),
        fabs(measurement->gyro.z - gyroPrev.z)
    };

    vec3_t magGrad = {
        fabs(measurement->mag.x - magPrev.x),
        fabs(measurement->mag.y - magPrev.y),
        fabs(measurement->mag.z - magPrev.z)
    };

    // Adaptive Smoothing Factor (Decrease Filtering if Gradient is High)
    float k_acc = 1.0f / (1.0f + accGrad.x + accGrad.y + accGrad.z);
    float k_gyro = 1.0f / (1.0f + gyroGrad.x + gyroGrad.y + gyroGrad.z);
    float k_mag = 1.0f / (1.0f + magGrad.x + magGrad.y + magGrad.z);

    float ALPHA_ACC_ADAPT = k_acc * ALPHA_ACC_LPF;
    float ALPHA_GYRO_ADAPT = k_gyro * ALPHA_GYRO_LPF;
    float ALPHA_MAG_ADAPT = k_mag * ALPHA_MAG_LPF;

    // Apply Adaptive Low-Pass Filtering
    measurement->acc_LPF.x = (1 - ALPHA_ACC_ADAPT) * measurement->acc_LPF.x + ALPHA_ACC_ADAPT * measurement->acc.x;
    measurement->acc_LPF.y = (1 - ALPHA_ACC_ADAPT) * measurement->acc_LPF.y + ALPHA_ACC_ADAPT * measurement->acc.y;
    measurement->acc_LPF.z = (1 - ALPHA_ACC_ADAPT) * measurement->acc_LPF.z + ALPHA_ACC_ADAPT * measurement->acc.z;

    measurement->gyro_LPF.x = (1 - ALPHA_GYRO_ADAPT) * measurement->gyro_LPF.x + ALPHA_GYRO_ADAPT * measurement->gyro.x;
    measurement->gyro_LPF.y = (1 - ALPHA_GYRO_ADAPT) * measurement->gyro_LPF.y + ALPHA_GYRO_ADAPT * measurement->gyro.y;
    measurement->gyro_LPF.z = (1 - ALPHA_GYRO_ADAPT) * measurement->gyro_LPF.z + ALPHA_GYRO_ADAPT * measurement->gyro.z;

    measurement->mag_LPF.x = (1 - ALPHA_MAG_ADAPT) * measurement->mag_LPF.x + ALPHA_MAG_ADAPT * measurement->mag.x;
    measurement->mag_LPF.y = (1 - ALPHA_MAG_ADAPT) * measurement->mag_LPF.y + ALPHA_MAG_ADAPT * measurement->mag.y;
    measurement->mag_LPF.z = (1 - ALPHA_MAG_ADAPT) * measurement->mag_LPF.z + ALPHA_MAG_ADAPT * measurement->mag.z;

    // Apply High-Pass Filtering to Gyro
    measurement->gyro_HPF.x = ALPHA_HPF * (measurement->gyro_HPF.x + measurement->gyro.x - gyroPrev.x);
    measurement->gyro_HPF.y = ALPHA_HPF * (measurement->gyro_HPF.y + measurement->gyro.y - gyroPrev.y);
    measurement->gyro_HPF.z = ALPHA_HPF * (measurement->gyro_HPF.z + measurement->gyro.z - gyroPrev.z);

    // Store Previous Values
    accPrev = measurement->acc;
    gyroPrev = measurement->gyro;
    magPrev = measurement->mag;
}
