#include <Arduino.h>
#include "CompClass.h"

CompFilter::CompFilter(magwick_data_t* filter_data) {
    _High_Beta = filter_data->high_beta;
    _Low_Beta = filter_data->low_beta;
    _Default_Beta = filter_data->std_beta;
}

void CompFilter::UpdateQ(vec3_t* gyro, vec3_t* acc, float dt) {
    float recipNorm;
    float s0, s1, s2, s3;
    float qDot1, qDot2, qDot3, qDot4;
    float _2qw, _2qx, _2qy, _2qz, _4qw, _4qx, _4qy, _8qx, _8qy, qwqw, qxqx, qyqy, qzqz;

    // Model based time propagation
    qDot1 = 0.5f * (-q.x * gyro->x - q.y * gyro->y - q.z * gyro->z);
    qDot2 = 0.5f * (q.w * gyro->x + q.y * gyro->z - q.z * gyro->y);
    qDot3 = 0.5f * (q.w * gyro->y - q.x * gyro->z + q.z * gyro->x);
    qDot4 = 0.5f * (q.w * gyro->z + q.x * gyro->y - q.y * gyro->x);

    float BETA = calculateDynamicBeta(*acc);
    // float BETA = DEFAULT_BETA;

    if (!(acc->x == 0.0 && acc->y == 0.0 && acc->z == 0.0)) {
        // Normalise accelerometer measurement
        recipNorm = invSqrt(acc->x * acc->x + acc->y * acc->y + acc->z * acc->z);
        acc->x *= recipNorm;
        acc->y *= recipNorm;
        acc->z *= recipNorm;

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
        s0 = _4qw * qyqy + _2qy * acc->x + _4qw * qxqx - _2qx * acc->y;
        s1 = _4qx * qzqz - _2qz * acc->x + 4.0f * qwqw * q.x - _2qw * acc->y - _4qx + _8qx * qxqx + _8qx * qyqy + _4qx * acc->z;
        s2 = 4.0f * qwqw * q.y + _2qw * acc->x + _4qy * qzqz - _2qz * acc->y - _4qy + _8qy * qxqx + _8qy * qyqy + _4qy * acc->z;
        s3 = 4.0f * qxqx * q.z - _2qx * acc->x + 4.0f * qyqy * q.z - _2qy * acc->y;

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

void CompFilter::GetEulerRPYdeg(attitude_s* rpy) {
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
    long i;
    static_assert(sizeof(float) == sizeof(long), "float and long must be the same size");
    memcpy(&i, &y, sizeof(float));
    i = 0x5f3759df - (i >> 1);
    memcpy(&y, &i, sizeof(float));
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

float CompFilter::calculateDynamicBeta(vec3_t acc) {
    // Compute the norm (magnitude) of the accelerometer vector
    accNorm = abs(sqrtf(acc.x * acc.x + acc.y * acc.y + acc.z * acc.z)/G-1) ;
    // Adapt Beta based on accelerometer norm
    if (accNorm < 0.25) {
        Serial.println("Rely_more");

        // System is likely stable or slow-moving, increase Beta for more correction
        filter_beta = Beta::Rely_more;

    } else if (accNorm > 0.5) {
        Serial.println("Rely_less");
        filter_beta = Beta::Rely_less;

    } else {
        Serial.println("amit");
        filter_beta = Beta::Std_factor;
    }

    switch (filter_beta)
    {
    case Beta::Rely_more:
        return _High_Beta;
    case Beta::Rely_less:
        return _Low_Beta;
    case Beta::Std_factor:
        return _Default_Beta;
    }
}

void CompFilter::set_beta(magwick_data_t* new_data) {
    _High_Beta = new_data->high_beta;
    _Low_Beta = new_data->low_beta;
    _Default_Beta = new_data->std_beta;
}