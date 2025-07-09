#include "IMU_type.h"

IMU_Func::IMU_Func(Measurement_t* meas, int ODR, int G_FS, int A_FS, int G_LPF_FREQ, int A_LPF_FREQ, bool EN_LPF) : _IMU() {
    _meas = meas; // Initialize the static pointer to the measurement struct
    // Set the ODR rate based on the input parameter
    Serial.print("ODR: ");
    Serial.print(ODR);
    Serial.print(",");
    Serial.print("G_FS: ");
    Serial.print(G_FS);
    Serial.print(",");
    Serial.print("A_FS: ");
    Serial.print(A_FS);
    Serial.print(",");
    
    switch (ODR) {
        case 416:
            ODR_REG = 0b01100000; // 416 Hz
            break;
        case 833:
            ODR_REG = 0b01110000; // 833 Hz
            break;
        default:
            Serial.println("Unsupported ODR_RATE. Defaulting to 416 Hz.");
            ODR_REG = 0b01100000; // Default to 416 Hz
            break;
    }
    switch(G_FS) {
        case 250:
            GYRO_FS_REG = 0b00000000; // 250 dps
            GYRO_SENS = 8.75/1000; // Sensitivity for 250 dps
            break;
        case 500:
            GYRO_FS_REG = 0b00000100; // 500 dps
            GYRO_SENS = 17.5/1000; // Sensitivity for 500 dps
            break;
        case 1000:
            GYRO_FS_REG = 0b00001000; // 1000 dps
            GYRO_SENS = 35/1000; // Sensitivity for 1000 dps
            break;
        default:
            Serial.println("Unsupported GYRO_FS. Defaulting to 500 dps.");
            GYRO_FS_REG = 0b00000100; // Default to 500 dps
            GYRO_SENS = 17.5/1000; // Default sensitivity for 500 dps
            break;
    }
    switch(A_FS) {
        case 2:
            ACC_FS_REG = 0b00000000; // 2 g
            ACC_SENS = 0.061/1000; // Sensitivity for 2 g
            break;
        case 4:
            ACC_FS_REG = 0b00001000; // 4 g
            ACC_SENS = 0.122/1000; // Sensitivity for 4 g
            break;
        case 8:
            ACC_FS_REG = 0b00001100; // 8 g
            ACC_SENS = 0.244/1000; // Sensitivity for 8 g
            break;
        default:
            Serial.println("Unsupported ACC_FS. Defaulting to 4 g.");
            ACC_FS_REG = 0b00001000; // Default to 4 g
            ACC_SENS = 0.122/1000; // Default sensitivity for 4 g
            break;
    }
    if (EN_LPF) {
        GYRO_LPF_EN = 0b00000010; // Enable LPF1 for Gyro
        switch(G_LPF_FREQ) {
            case 25:
                GYRO_LPF_REG = 0b00001110; // LPF1 bandwidth at 25 Hz
                break;
            case 49:
                GYRO_LPF_REG = 0b00001101; // LPF1 bandwidth at 49 Hz
                break;
            case 12:
                GYRO_LPF_REG = 0b00001100; // LPF1 bandwidth at 12.5 Hz
                break;
            default:
                Serial.println("Unsupported GYRO_LPF_FREQ. Defaulting to 25 Hz.");
                GYRO_LPF_REG = 0b00001110; // Default to 25 Hz
                break;
            }
        switch(A_LPF_FREQ) {
            case 20:
                ACC_LPF_REG = 0b01001000; // LPF2 bandwidth at ODR/20
                break;
            case 45:
                ACC_LPF_REG = 0b01101000; // LPF2 bandwidth at ODR/45
                break;
            case 100:
                ACC_LPF_REG = 0b10001100; // LPF2 bandwidth at ODR/100
                break;
            default:
                Serial.println("Unsupported ACC_LPF_FREQ_DIV. Defaulting to 20 Hz.");
                ACC_LPF_REG = 0b01001000; // Default to ODR/20
                break;
            }
        } else {
            GYRO_LPF_REG = 0b00000000; // No LPF
            ACC_LPF_REG = 0b00000000; // No LPF
            }
}

void IMU_Func::init_IMU() {
    // Your implementation here
    // For example:
    Wire.begin();
    
    // Initialize IMU
    if (!_IMU.init()) {
        Serial.println("Failed to detect and initialize IMU!");
        while (1);
    }
    

    _IMU.enableDefault();

    // Setting up the Gyro-
    _IMU.writeReg(LSM6::CTRL2_G, (ODR_REG | GYRO_FS_REG));
    if (GYRO_LPF_EN != 0b00000000) {
            _IMU.writeReg(LSM6::CTRL4_C, GYRO_LPF_EN);
            _IMU.writeReg(LSM6::CTRL6_C, GYRO_LPF_REG);
    }

    // Setting up the Accelerometer
    _IMU.writeReg(LSM6::CTRL1_XL, (ODR_REG | ACC_FS_REG));
    if (ACC_LPF_EN != 0b00000000) {
        _IMU.writeReg(LSM6::CTRL8_XL, ACC_LPF_REG);
    }
}

void IMU_Func::Read_IMU() {
    _IMU.read();
    _meas->acc.x = _IMU.a.x * ACC_SENS * G - _meas->acc_bias.x;
    _meas->acc.y = _IMU.a.y * ACC_SENS * G - _meas->acc_bias.y;
    _meas->acc.z = _IMU.a.z * ACC_SENS * G;
    if (abs(_meas->acc.x) < IMU_THRESHOLD) { _meas->acc.x = 0;}
    if (abs(_meas->acc.y) < IMU_THRESHOLD) { _meas->acc.y = 0;}
    // if (abs(_meas->acc.z) < IMU_THRESHOLD) { _meas->acc.z = 0;}

    _meas->gyroDEG.x = _IMU.g.x * GYRO_SENS - _meas->gyro_bias.x;
    _meas->gyroDEG.y = _IMU.g.y * GYRO_SENS - _meas->gyro_bias.y;
    _meas->gyroDEG.z = _IMU.g.z * GYRO_SENS - _meas->gyro_bias.z;
    _meas->gyroRAD.x = _meas->gyroDEG.x * deg2rad;
    _meas->gyroRAD.y = _meas->gyroDEG.y * deg2rad;
    _meas->gyroRAD.z = _meas->gyroDEG.z * deg2rad;

}


void IMU_Func::Initial_Calibration(){
    Serial.println("Starting IMU Calibration...");

    int start_time = millis();
    int num_samples = 0;
    while (millis() - start_time < 10000){
      _IMU.read();
      float x = _IMU.g.x * GYRO_SENS;
      float y = _IMU.g.y * GYRO_SENS;
      float z = _IMU.g.z * GYRO_SENS;
      num_samples++;
      _meas->gyro_bias.x += (x - _meas->gyro_bias.x)/num_samples;
      _meas->gyro_bias.y += (y - _meas->gyro_bias.y)/num_samples;
      _meas->gyro_bias.z += (z - _meas->gyro_bias.z)/num_samples;

      _meas->acc_bias.x += (_IMU.a.x * ACC_SENS * G - _meas->acc_bias.x)/num_samples;
      _meas->acc_bias.y += (_IMU.a.y * ACC_SENS * G - _meas->acc_bias.y)/num_samples;
    //   _meas->acc_bias.z += (_IMU.a.z * ACC_SENS - _meas->acc_bias.z)/num_samples;
    }    
    Serial.println("Finished Gyro calibration");
    delay(2000);

}