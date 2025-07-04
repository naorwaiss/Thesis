#include <math.h>
#include "Madgwick.h"

Madgwick::Madgwick(Measurement_t* meas_data,attitude_t *estimated_attitude,quat_t* quaternion,float sampleFreq ,float beta) {
    this->_beta = beta;
	this->_sample_hz = sampleFreq;
    q0 = 1.0f;
    q1 = 0.0f;
    q2 = 0.0f;
    q3 = 0.0f;
    _dt_sec = 1.0f / sampleFreq;
    anglesComputed = 0;
    this->_meas = meas_data;
	this->_estimated_attitude = estimated_attitude;
	this->_quaternion = quaternion;
}


//-------------------------------------------------------------------------------------------
// IMU algorithm update

void Madgwick::updateIMU(float gx, float gy, float gz, float ax, float ay, float az) {
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	// Convert gyroscope degrees/sec to radians/sec
	// gx *= 0.0174533f;
	// gy *= 0.0174533f;
	// gz *= 0.0174533f;


	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_4q0 = 4.0f * q0;
		_4q1 = 4.0f * q1;
		_4q2 = 4.0f * q2;
		_8q1 = 8.0f * q1;
		_8q2 = 8.0f * q2;
		q0q0 = q0 * q0;
		q1q1 = q1 * q1;
		q2q2 = q2 * q2;
		q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= _beta * s0;
		qDot2 -= _beta * s1;
		qDot3 -= _beta * s2;
		qDot4 -= _beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * _dt_sec;
	q1 += qDot2 * _dt_sec;
	q2 += qDot3 * _dt_sec;
	q3 += qDot4 * _dt_sec;

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
	anglesComputed = 0;
}


void Madgwick::madgwick_operation() {
    updateIMU(_meas->gyroRAD.x, _meas->gyroRAD.y, _meas->gyroRAD.z, _meas->acc.x, _meas->acc.y, _meas->acc.z);
	_quaternion->x = q0;
	_quaternion->y = q1;
	_quaternion->z = q2;
	_quaternion->w = q3;
	_estimated_attitude->pitch = getPitch();
	_estimated_attitude->roll = getRoll();
	_estimated_attitude->yaw = getYaw();
}


float Madgwick::invSqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    y = y * (1.5f - (halfx * y * y));
    return y;
}

//-------------------------------------------------------------------------------------------

void Madgwick::computeAngles() {
    roll = atan2f(q0 * q1 + q2 * q3, 0.5f - q1 * q1 - q2 * q2);
    pitch = asinf(-2.0f * (q1 * q3 - q0 * q2));
    yaw = atan2f(q1 * q2 + q0 * q3, 0.5f - q2 * q2 - q3 * q3);
 
}


void Madgwick::set_zero(float ati , float thrshold) {
    if (abs(ati) < thrshold && abs(ati) > -thrshold) {
        ati = 0;
    }
}