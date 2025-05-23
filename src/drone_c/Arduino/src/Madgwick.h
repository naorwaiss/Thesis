#ifndef Madgwick_h
#define Madgwick_h

#include "Var_types.h"

class Madgwick {
   private:
    static float invSqrt(float x);
    float beta;  // algorithm gain
    float q0;
    float q1;
    float q2;
    float q3;  // quaternion of sensor frame relative to auxiliary frame
    float invSampleFreq;
    float roll;
    float pitch;
    float yaw;
    char anglesComputed;
    void computeAngles();
    quat_t* _quaternion;
    Measurement_t* _meas;
    attitude_t* _estimated_attitude;
    float _beta;
    float _sample_hz;

    //-------------------------------------------------------------------------------------------
    // Function declarations
   public:
    Madgwick(Measurement_t* meas_data, attitude_t* estimated_attitude, quat_t* quaternion, float sampleFreq, float beta);
    void begin(float sampleFrequency) { invSampleFreq = 1.0f / sampleFrequency; }
    void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void updateIMU(float gx, float gy, float gz, float ax, float ay, float az);
    void madgwick_operation();

    // Getter functions
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
};
#endif
