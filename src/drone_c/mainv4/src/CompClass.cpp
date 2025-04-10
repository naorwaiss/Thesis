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
    InitialFiltering(meas);

    // Model based time propagation
    // qDot1 = 0.5f * (-q.x * meas->gyro_HPF.x - q.y * meas->gyro_HPF.y - q.z * meas->gyro_HPF.z);
    // qDot2 = 0.5f * (q.w * meas->gyro_HPF.x + q.y * meas->gyro_HPF.z - q.z * meas->gyro_HPF.y);
    // qDot3 = 0.5f * (q.w * meas->gyro_HPF.y - q.x * meas->gyro_HPF.z + q.z * meas->gyro_HPF.x);
    // qDot4 = 0.5f * (q.w * meas->gyro_HPF.z + q.x * meas->gyro_HPF.y - q.y * meas->gyro_HPF.x);
    qDot1 = 0.5f * (-q.x * meas->gyro_HPF.x - q.y * meas->gyro_HPF.y - q.z * meas->gyro_HPF.z);
    qDot2 = 0.5f * (q.w * meas->gyro_HPF.x + q.y * meas->gyro_HPF.z - q.z * meas->gyro_HPF.y);
    qDot3 = 0.5f * (q.w * meas->gyro_HPF.y - q.x * meas->gyro_HPF.z + q.z * meas->gyro_HPF.x);
    qDot4 = 0.5f * (q.w * meas->gyro_HPF.z + q.x * meas->gyro_HPF.y - q.y * meas->gyro_HPF.x);
    
    float BETA = calculateDynamicBeta(*meas);
    // float BETA = DEFAULT_BETA;

    if (!(meas->acc_LPF.x == 0.0 && meas->acc_LPF.y == 0.0 && meas->acc_LPF.z == 0.0)) {
        // Normalise accelerometer measurement
        recipNorm = invSqrt(meas->acc_LPF.x * meas->acc_LPF.x + meas->acc_LPF.y * meas->acc_LPF.y + meas->acc_LPF.z * meas->acc_LPF.z);
        meas->acc_LPF.x *= recipNorm;
        meas->acc_LPF.y *= recipNorm;
        meas->acc_LPF.z *= recipNorm;

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
        s0 = _4qw * qyqy + _2qy * meas->acc_LPF.x + _4qw * qxqx - _2qx * meas->acc_LPF.y;
        s1 = _4qx * qzqz - _2qz * meas->acc_LPF.x + 4.0f * qwqw * q.x - _2qw * meas->acc_LPF.y - _4qx + _8qx * qxqx + _8qx * qyqy + _4qx * meas->acc_LPF.z;
        s2 = 4.0f * qwqw * q.y + _2qw * meas->acc_LPF.x + _4qy * qzqz - _2qz * meas->acc_LPF.y - _4qy + _8qy * qxqx + _8qy * qyqy + _4qy * meas->acc_LPF.z;
        s3 = 4.0f * qxqx * q.z - _2qx * meas->acc_LPF.x + 4.0f * qyqy * q.z - _2qy * meas->acc_LPF.y;

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
    // if(USE_MAG &&( meas->mag_LPF.x != 0.0 && meas->mag_LPF.y != 0.0 && meas->mag_LPF.z != 0.0) && (gyroNorm < HIGH_MOTION)){ // Try to check if it works better only when gyro norm is low
    if (USE_MAG && (meas->mag_LPF.x != 0.0 && meas->mag_LPF.y != 0.0 && meas->mag_LPF.z != 0.0) && (gyroNorm < HIGH_MOTION)) {
        // if(USE_MAG &&( meas->mag_LPF.x != 0.0 && meas->mag_LPF.y != 0.0 && meas->mag_LPF.z != 0.0)){

        // Normalise magnetometer measurement
        recipNorm = invSqrt(meas->mag_LPF.x * meas->mag_LPF.x + meas->mag_LPF.y * meas->mag_LPF.y + meas->mag_LPF.z * meas->mag_LPF.z);
        meas->mag_LPF.x *= recipNorm;
        meas->mag_LPF.y *= recipNorm;
        meas->mag_LPF.z *= recipNorm;

        _2qwmx = 2.0f * q.w * meas->mag_LPF.x;
        _2qwmy = 2.0f * q.w * meas->mag_LPF.y;
        _2qwmz = 2.0f * q.w * meas->mag_LPF.z;
        _2qxmx = 2.0f * q.x * meas->mag_LPF.x;
        _2q0 = 2.0f * q.w;
        _2q1 = 2.0f * q.x;
        _2q2 = 2.0f * q.y;
        _2q3 = 2.0f * q.z;
        _2q0q2 = 2.0f * q.w * q.y;
        _2q0q1 = 2.0f * q.w * q.x;
        _2q0q3 = 2.0f * q.w * q.z;
        _2q2q3 = 2.0f * q.y * q.z;
        q0q0 = q.w * q.w;
        q0q1 = q.w * q.x;
        q0q2 = q.w * q.y;
        q0q3 = q.w * q.z;
        q1q1 = q.x * q.x;
        q1q2 = q.x * q.y;
        q1q3 = q.x * q.z;
        q2q2 = q.y * q.y;
        q2q3 = q.y * q.z;
        q3q3 = q.z * q.z;

        // Reference direction of Earth's magnetic field
        hx = meas->mag_LPF.x * q0q0 - _2qwmy * q.z + _2qwmz * q.y + meas->mag_LPF.x * q1q1 + _2qxmx * q.y + meas->mag_LPF.x * q2q2 - meas->mag_LPF.x * q3q3;
        hy = _2qwmx * q.z + meas->mag_LPF.y * q0q0 - _2qwmz * q.x + _2q0 * meas->mag_LPF.y * q1q1 - meas->mag_LPF.y * q2q2 + meas->mag_LPF.y * q3q3 + _2qxmx * q.z;
        _2bx = sqrtf(hx * hx + hy * hy);
        _2bz = -_2qwmx * q.y + _2q0 * meas->mag_LPF.z * q1q1 + _2q0 * meas->mag_LPF.z * q2q2 + meas->mag_LPF.z * q3q3 + _2qxmx * q.y - meas->mag_LPF.z * q0q0;
        _4bx = 2.0f * _2bx;
        _4bz = 2.0f * _2bz;

        // Gradient decent algorithm corrective step
        s0 = -_2bz * q.y * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - meas->mag_LPF.z) + (-_2bx * q.z + _2bz * q.x) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - meas->mag_LPF.x);
        s1 = -4.0f * q.x * (1 - 2.0f * q1q1 - 2.0f * q2q2 - meas->mag_LPF.z) + _2bz * q.z * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - meas->mag_LPF.z) + (_2bx * q.y + _2bz * q.x) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - meas->mag_LPF.x);
        s2 = -4.0f * q.y * (1 - 2.0f * q1q1 - 2.0f * q2q2 - meas->mag_LPF.z) + (-_2bx * q.y + _2bz * q.x) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - meas->mag_LPF.z) + (_2bx * q.z + _2bz * q.x) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - meas->mag_LPF.x);
        s3 = (-_4bx * q.y * (2.0f * q1q2 - _2q0q3 - meas->mag_LPF.z) + _4bz * q.z * (2.0f * q1q3 - _2q0q2 - meas->mag_LPF.x) - _4bx * q.x * (2.0f * q2q3 - _2q0q1 - meas->mag_LPF.y)) + (-_4bx * q.z + _4bz * q.x) * (_4bx * (0.5f - q2q2 - q3q3) + _4bz * (q1q3 - q0q2) - meas->mag_LPF.x);
        recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);  // normalise step magnitude
        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        float magTrust = 0.3f;
        // if (gyroNorm > HIGH_MOTION) {
        //     magTrust = 0.0f; // Less influence during high motion
        // } else if (gyroNorm < LOW_MOTION) {
        //     magTrust = 0.3f; // More influence during low motion
        // }

        // Apply feedback step
        qDot1 -= magTrust * BETA * s0;
        qDot2 -= magTrust * BETA * s1;
        qDot3 -= magTrust * BETA * s2;
        qDot4 -= magTrust * BETA * s3;
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
    gyroNorm = sqrtf(meas.gyro_HPF.x * meas.gyro_HPF.x +
                     meas.gyro_HPF.y * meas.gyro_HPF.y +
                     meas.gyro_HPF.z * meas.gyro_HPF.z);
    // Adapt Beta based on gyroscope norm
    if (gyroNorm < LOW_MOTION) {
        // System is likely stable or slow-moving, increase Beta for more correction
        // Serial.println("Low Motion");
        return HIGH_BETA;
    } else if (gyroNorm > HIGH_MOTION) {
        // System is moving fast, reduce Beta to rely more on gyroscope
        // Serial.println("High Motion");
        return LOW_BETA;
    } else {
        // Default case, normal correction
        // Serial.println("Default Motion");
        return DEFAULT_BETA;
    }
}

// float CompFilter::calculateDynamicBeta(Measurement_t meas) {
//     gyroNorm = sqrtf(meas.gyro_HPF.x * meas.gyro_HPF.x +
//                    meas.gyro_HPF.y * meas.gyro_HPF.y +
//                    meas.gyro_HPF.z * meas.gyro_HPF.z);

//     // More consistent beta values with hysteresis
//     static float lastBeta = DEFAULT_BETA;
//     static const float HYSTERESIS = 0.05f;

//     if (gyroNorm > (LOW_MOTION + HYSTERESIS) || lastBeta == HIGH_BETA) {
//         if (gyroNorm < (LOW_MOTION - HYSTERESIS))
//             lastBeta = LOW_BETA;
//         else
//             lastBeta = HIGH_BETA;
//     }

//     return lastBeta;
// }

void CompFilter::InitialFiltering(Measurement_t* meas){
    
    meas->acc_LPF.x = (1 - ALPHA_ACC_LPF) * meas->acc.x + ALPHA_ACC_LPF * meas->acc_LPF.x;
    meas->acc_LPF.y = (1 - ALPHA_ACC_LPF) * meas->acc.y + ALPHA_ACC_LPF * meas->acc_LPF.y;
    meas->acc_LPF.z = (1 - ALPHA_ACC_LPF) * meas->acc.z + ALPHA_ACC_LPF * meas->acc_LPF.z;

    // Apply High-pass Filter to Gyro - > RAD. Used for the filter
    static vec3_t gyroPrev = {0.0, 0.0, 0.0};
    meas->gyro_HPF.x = ALPHA_HPF * (meas->gyro_HPF.x + meas->gyroRAD.x - gyroPrev.x);
    meas->gyro_HPF.y = ALPHA_HPF * (meas->gyro_HPF.y + meas->gyroRAD.y - gyroPrev.y);
    meas->gyro_HPF.z = ALPHA_HPF * (meas->gyro_HPF.z + meas->gyroRAD.z - gyroPrev.z);
    gyroPrev.x = meas->gyroRAD.x;
    gyroPrev.y = meas->gyroRAD.y;
    gyroPrev.z = meas->gyroRAD.z;
    
    // Apply Low-pass Filter to Gyro - > DEG. Used for acro
    meas->gyro_LPF.x = (1 - ALPHA_GYRO_LPF) * meas->gyroDEG.x + ALPHA_GYRO_LPF * meas->gyro_LPF.x;
    meas->gyro_LPF.y = (1 - ALPHA_GYRO_LPF) * meas->gyroDEG.y + ALPHA_GYRO_LPF * meas->gyro_LPF.y;
    meas->gyro_LPF.z = (1 - ALPHA_GYRO_LPF) * meas->gyroDEG.z + ALPHA_GYRO_LPF * meas->gyro_LPF.z;

    if (USE_MAG) {
        // Apply Low-pass Filter to Mag
        meas->mag_LPF.x = (1 - ALPHA_MAG_LPF) * meas->mag.x + ALPHA_MAG_LPF * meas->mag_LPF.x;
        meas->mag_LPF.y = (1 - ALPHA_MAG_LPF) * meas->mag.y + ALPHA_MAG_LPF * meas->mag_LPF.y;
        meas->mag_LPF.z = (1 - ALPHA_MAG_LPF) * meas->mag.z + ALPHA_MAG_LPF * meas->mag_LPF.z;
    }

}
