//=============================================================================================
// MadgwickAHRS.h
//=============================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
//
// From the x-io website "Open-source resources available on this website are
// provided under the GNU General Public Licence unless an alternative licence
// is provided in source."
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=============================================================================================
#ifndef IMUMADGWICK_H
#define IMUMADGWICK_H
#include <math.h>
#include "Wire.h"
#include <Arduino.h>

// IMU Register definitions
#define WHO_AM_I_REG 0x75
#define PWR_MGMT0_REG 0x4E
#define ACCEL_DATA_X1 0x1F
#define GYRO_DATA_X1 0x25
#define GYRO_CONFIG0 0x4F
#define ACCEL_CONFIG0 0x50
#define IIM42652_ADDR 0x68

struct vec3 {
    float x;
    float y;
    float z;
};

typedef struct
{
    float q0;
    float q1;
    float q2;
    float q3;
} quaternion_t;


typedef struct
{
    float roll;
    float pitch;
    float yaw;
} atitude_t;

struct imu_data {
    vec3 accel;
    vec3 gyro;
    quaternion_t quaternion;
    atitude_t atitude;
};




//--------------------------------------------------------------------------------------------
// Variable declaration
class ImuMadgwick{
private:
    static float invSqrt(float x);
    float beta;				// algorithm gain
    float q0;
    float q1;
    float q2;
    float q3;	// quaternion of sensor frame relative to auxiliary frame
    float invSampleFreq;
    float roll;
    float pitch;
    float yaw;
    char anglesComputed;
    quaternion_t quaternion;
    TwoWire* wire;
    double dt_sec;
    const float ACCEL_SENS_LSB_TO_MG = 0.12207;    // mg per LSB at ±4g
    const float GYRO_SENS_LSB_TO_DPS = 0.0152588;  // degrees per second per LSB at ±500 dps
    const float ACCEL_SENS_LSB_TO_MS2 = ACCEL_SENS_LSB_TO_MG * GRAVITY / 1000.0;  // m/s^2 per LSB
    const float GRAVITY = 9.80665;                                                // m/s^2

    
    // Helper functions for I2C communication
    void computeAngles();
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    int16_t read16bit(uint8_t reg);
    void imu_update();
//-------------------------------------------------------------------------------------------
// Function declarations
public:
    ImuMadgwick(TwoWire* wireInstance,double sampleFrequency);
    imu_data imu_measurement;
    void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void updateIMU(float gx, float gy, float gz, float ax, float ay, float az);
    //float getPitch(){return atan2f(2.0f * q2 * q3 - 2.0f * q0 * q1, 2.0f * q0 * q0 + 2.0f * q3 * q3 - 1.0f);};
    //float getRoll(){return -1.0f * asinf(2.0f * q1 * q3 + 2.0f * q0 * q2);};
    //float getYaw(){return atan2f(2.0f * q1 * q2 - 2.0f * q0 * q3, 2.0f * q0 * q0 + 2.0f * q1 * q1 - 1.0f);};
    void init_imu_orientation();
    void imu_operation_process();
    float getRoll() {
        if (!anglesComputed) computeAngles();
        return roll * 57.29578f;
    }
    float getPitch() {
        if (!anglesComputed) computeAngles();
        return pitch * 57.29578f;
    }
    float getYaw() {
        if (!anglesComputed) computeAngles();
        return yaw * 57.29578f + 180.0f;
    }
    float getRollRadians() {
        if (!anglesComputed) computeAngles();
        return roll;
    }
    float getPitchRadians() {
        if (!anglesComputed) computeAngles();
        return pitch;
    }
    float getYawRadians() {
        if (!anglesComputed) computeAngles();
        return yaw;
    }
    quaternion_t getQuaternion() {
        return {q0, q1, q2, q3};
    }
};
#endif

