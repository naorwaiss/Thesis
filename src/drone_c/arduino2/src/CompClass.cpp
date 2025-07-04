#include <Arduino.h>
#include "CompClass.h"
#include "Var_types.h"

void CompFilter::UpdateQ(Measurement_t* meas, float dt) {
    float recipNorm;
    float s0, s1, s2, s3;
    float qDot1, qDot2, qDot3, qDot4;
    float _2qw, _2qx, _2qy, _2qz, _4qw, _4qx, _4qy, _8qx, _8qy, qwqw, qxqx, qyqy, qzqz;
    float _2qwmx, _2qwmy, _2qwmz, _2qxmx, _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3, q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3, _2q0q1, _2q0q3;
    float hx, hy, _2bx, _2bz, _4bx, _4bz;

    // Initial Filtering - Not a must nut it helps.
    // InitialFiltering(meas);

    // Model based time propagation
    // qDot1 = 0.5f * (-q.x * meas->gyro_LPF.x - q.y * meas->gyro_LPF.y - q.z * meas->gyro_LPF.z);
    // qDot2 = 0.5f * (q.w * meas->gyro_LPF.x + q.y * meas->gyro_LPF.z - q.z * meas->gyro_LPF.y);
    // qDot3 = 0.5f * (q.w * meas->gyro_LPF.y - q.x * meas->gyro_LPF.z + q.z * meas->gyro_LPF.x);
    // qDot4 = 0.5f * (q.w * meas->gyro_LPF.z + q.x * meas->gyro_LPF.y - q.y * meas->gyro_LPF.x);

    qDot1 = 0.5f * (-q.x * meas->gyroRAD.x - q.y * meas->gyroRAD.y - q.z * meas->gyroRAD.z);
    qDot2 = 0.5f * (q.w * meas->gyroRAD.x + q.y * meas->gyroRAD.z - q.z * meas->gyroRAD.y);
    qDot3 = 0.5f * (q.w * meas->gyroRAD.y - q.x * meas->gyroRAD.z + q.z * meas->gyroRAD.x);
    qDot4 = 0.5f * (q.w * meas->gyroRAD.z + q.x * meas->gyroRAD.y - q.y * meas->gyroRAD.x);

    float BETA = calculateDynamicBeta(*meas);
    // float BETA = DEFAULT_BETA;

    if (!(meas->acc.x == 0.0 && meas->acc.y == 0.0 && meas->acc.z == 0.0)) {
        // Normalise accelerometer measurement
        recipNorm = invSqrt(meas->acc.x * meas->acc.x + meas->acc.y * meas->acc.y + meas->acc.z * meas->acc.z);
        meas->acc.x *= recipNorm;
        meas->acc.y *= recipNorm;
        meas->acc.z *= recipNorm;

        // Auxiliary variables to avoid repeated arithmetic
        _2qw = 2.0f * q.w;
        _2qx = 2.0f * q.x;
        _2qy = 2.0f * q.y;
        _2qz = 2.0f * q.z;
        _4qw = 4.0f * q.w;
        _4qx = 4.0f * q.x;
        _4qy = 4.0f * q.y;
        _8qx = 8.0f * q.x;
        _8qy = 8.0f * q.y;
        qwqw = q.w * q.w;
        qxqx = q.x * q.x;
        qyqy = q.y * q.y;
        qzqz = q.z * q.z;

        // Gradient decent algorithm corrective step
        s0 = _4qw * qyqy + _2qy * meas->acc.x + _4qw * qxqx - _2qx * meas->acc.y;
        s1 = _4qx * qzqz - _2qz * meas->acc.x + 4.0f * qwqw * q.x - _2qw * meas->acc.y - _4qx + _8qx * qxqx + _8qx * qyqy + _4qx * meas->acc.z;
        s2 = 4.0f * qwqw * q.y + _2qw * meas->acc.x + _4qy * qzqz - _2qz * meas->acc.y - _4qy + _8qy * qxqx + _8qy * qyqy + _4qy * meas->acc.z;
        s3 = 4.0f * qxqx * q.z - _2qx * meas->acc.x + 4.0f * qyqy * q.z - _2qy * meas->acc.y;

        recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);  // normalise step magnitude
        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        // Apply feedback step
        qDot1 -= BETA * s0;
        qDot2 -= BETA * s1;
        qDot3 -= BETA * s2;
        qDot4 -= BETA * s3;
    }

    // Integrate rate of change of quaternion to yield quaternion
    q.w += (qDot1 + qDot_prev.w) * dt / 2;
    q.x += (qDot2 + qDot_prev.x) * dt / 2;
    q.y += (qDot3 + qDot_prev.y) * dt / 2;
    q.z += (qDot4 + qDot_prev.z) * dt / 2;

    // Normalise quaternion in order to get unit length quaternion
    recipNorm = invSqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    q.w *= recipNorm;
    q.x *= recipNorm;
    q.y *= recipNorm;
    q.z *= recipNorm;

    estimatedGravityDir(&gravX, &gravY, &gravZ);
}

// Returning the estimated quaternion
void CompFilter::GetQuaternion(quat_t* q_) {
    q_->x = q.x;
    q_->y = q.y;
    q_->z = q.z;
    q_->w = q.w;
}

void CompFilter::GetEulerRPYrad(attitude_s* rpy, float initial_heading) {
    float gx = gravX;
    float gy = gravY;
    float gz = gravZ;

    if (gx > 1) gx = 1;
    if (gx < -1) gx = -1;

    // Currently returend in radians, can be converted to degrees by multiplying by rad2deg
    rpy->yaw = atan2f(2 * (q.w * q.z + q.x * q.y), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z);
    rpy->pitch = asinf(gx);
    // rpy->pitch = atan2f(2 * (q.w * q.y - q.x * q.z), 1 - 2 * (q.y * q.y + q.z * q.z));
    rpy->roll = atan2f(gy, gz);
}

void CompFilter::GetEulerRPYdeg(attitude_s* rpy, float initial_heading) {
    float gx = gravX;
    float gy = gravY;
    float gz = gravZ;
    if (gx > 1) gx = 1;
    if (gx < -1) gx = -1;

    rpy->yaw = atan2f(2 * (q.w * q.z + q.x * q.y), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z) * rad2deg;
    rpy->pitch = asinf(gx) * rad2deg;
    // rpy->pitch = atan2f(2 * (q.w * q.y - q.x * q.z), 1 - 2 * (q.y * q.y + q.z * q.z)) * rad2deg;
    rpy->roll = atan2f(2 * (q.w * q.x + q.y * q.z), 1 - 2 * (q.x * q.x + q.y * q.y)) * rad2deg;
    // rpy->roll = atan2f(gy, gz) * rad2deg;
}

//---------------------------------------------------------------------------------------------------
// Inverse square root function:
float CompFilter::invSqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

float CompFilter::GetAccZ(float ax, float ay, float az) {
    return (ax * gravX + ay * gravY + az * gravZ);
}

void CompFilter::estimatedGravityDir(float* gx, float* gy, float* gz) {
    *gx = 2 * (q.x * q.z - q.y * q.w);
    *gy = 2 * (q.y * q.z + q.x * q.w);
    *gz = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;
}

float CompFilter::calculateDynamicBeta(Measurement_t meas) {
    // Compute the norm (magnitude) of the gyroscope vector
    accNorm = sqrtf(meas.acc.x * meas.acc.x +
                     meas.acc.y * meas.acc.y +
                     meas.acc.z * meas.acc.z) *
               deg2rad;
    // Adapt Beta based on gyroscope norm
    if (accNorm < LOW_MOTION) {
        return HIGH_BETA;
    } else if (accNorm > HIGH_MOTION) {
        return LOW_BETA;
    } else {
        return DEFAULT_BETA;
    }
}

