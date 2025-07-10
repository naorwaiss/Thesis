#ifndef IMU_TYPE_H
#define IMU_TYPE_H


// IMU Sensor Libraries:
#include <LSM6.h>
#include <Wire.h>
#include "Var_types.h"

/*---------------------- Defining the class ----------------------*/
class IMU_Func{
    private:
        Measurement_t* _meas; // Pointer to the measurement struct
        LSM6 _IMU;          // IMU sensor object
        int ODR_REG;       // Output Data Rate Register
        int GYRO_FS_REG;   // Gyro Full Scale Register
        int ACC_FS_REG;    // Accelerometer Full Scale Register
        int GYRO_LPF_REG;  // Gyro Low Pass Filter Register
        int ACC_LPF_REG;   // Accelerometer Low Pass Filter Register
        int GYRO_LPF_EN;   // Gyro Low Pass Filter Enable
        int ACC_LPF_EN;    // Accelerometer Low Pass Filter Enable
        float GYRO_SENS;   // Gyro Sensitivity
        float ACC_SENS;    // Accelerometer Sensitivity
        const float IMU_THRESHOLD = 0.05;

        

    public:
        IMU_Func(Measurement_t* meas, int ODR = 416, int G_FS = 250, int A_FS = 2, int G_LPF_FREQ = 25, int A_LPF_FREQ = 20, bool EN_LPF = true);
        void init_IMU();
        void Read_IMU();
        void Initial_Calibration();

};

#endif // IMU_TYPE_H