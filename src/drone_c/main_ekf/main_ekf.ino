#include <Arduino.h>
#include "Wire.h"
#include <LSM6.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include "src/Var_types.h"
#include "src/Drone_com.h"
#include "src/ekf_filter.h"
#include <AlfredoCRSF.h>
#include "src/MotorsControl.h"
#include "src/PID_type.h"

// IMU Data Conversion Constants
#define POL_GYRO_SENS 8.75f / 1000.0f  // Gyro sensitivity FS = 125 dps
#define POL_ACC_SENS 0.02f / 1000.0f   // Accelerometer sensitivity
#define POL_MAG_SENS 1 / 6842.0f
#define IMU_TRASHOLD 0.04
#define crsfSerial Serial1  // Use Serial1 for the CRSF communication
#define MPU_TICK_RATE 10000

// old_drone
//  #define MOTOR1_PIN 2
//  #define MOTOR2_PIN 3
//  #define MOTOR3_PIN 5
//  #define MOTOR4_PIN 4
// old_drone

// new drone
#define MOTOR1_PIN 2
#define MOTOR2_PIN 3
#define MOTOR3_PIN 4
#define MOTOR4_PIN 5
// new drone

#define MAX_ANGLE 15.0f
#define MAX_RATE 200.0f
#define CONTROLLER_MIN 988
#define CONTROLLER_MAX 2012
#define IMU_TRASHOLD 0.04

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// Struct Definitions
AlfredoCRSF crsf;
Controller_s controller_data;
Measurement_t meas;
EKF ekf(&meas);
LSM6 IMU;
LIS3MDL mag;
attitude_t euiler;
quat_t q_est;
Motors motors(MOTOR1_PIN, MOTOR2_PIN, MOTOR3_PIN, MOTOR4_PIN);
bool is_armed = false;
bool is_armed_amit_flag = false;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    IMU_init();
    GyroMagCalibration();
    ekf.init_EKF();
}

unsigned long dt;
void loop() {
    unsigned long start_time = micros();
    Update_measurement();
    euiler = ekf.single_process_imu(dt);
    q_est = ekf.eulerToQuaternion(&euiler);



    Serial.print("EKF Roll: ");
    Serial.println(euiler.roll);
    Serial.print("EKF Pitch: ");
    Serial.println(euiler.pitch);
    Serial.print("EKF Yaw: ");
    Serial.println(euiler.yaw);
    Serial.print("quart w : ");
    Serial.println(q_est.w);
    Serial.print("quat x : ");
    Serial.println(q_est.x);
    Serial.print("quat y : ");
    Serial.println(q_est.y);
    Serial.print("quat z : ");
    Serial.println(q_est.z);


    unsigned long end_time = micros();       // End time
    dt = end_time - start_time;  // Compute execution time

}

void Update_measurement() {
    IMU.read();
    mag.read();
    meas.acc.x = IMU.a.x * POL_ACC_SENS ;
    meas.acc.y = IMU.a.y * POL_ACC_SENS ;
    meas.acc.z = IMU.a.z * POL_ACC_SENS ;
 
    if (abs(meas.acc.x) < IMU_TRASHOLD) {
        meas.acc.x = 0;
    }
    if (abs(meas.acc.y) < IMU_TRASHOLD) {
        meas.acc.y = 0;
    }
    if (abs(meas.acc.z) < IMU_TRASHOLD) {
        meas.acc.z = 0;
    }

    meas.gyro.x = IMU.g.x * POL_GYRO_SENS; 
    meas.gyro.y = IMU.g.y * POL_GYRO_SENS;
    meas.gyro.z = IMU.g.z * POL_GYRO_SENS;
    if (abs(meas.gyro.x) < IMU_TRASHOLD) {
        meas.gyro.x = 0;
    }
    if (abs(meas.gyro.y) < IMU_TRASHOLD) {
        meas.gyro.y = 0;
    }
    if (abs(meas.gyro.z) < IMU_TRASHOLD) {
        meas.gyro.z = 0;
    }
    meas.mag.x = mag.m.x * POL_MAG_SENS;
    meas.mag.y = mag.m.y * POL_MAG_SENS;
    meas.mag.z = mag.m.z * POL_MAG_SENS;
    // if (abs(meas.mag.x < IMU_TRASHOLD)) {
    //     meas.mag.x = 0;
    // }
    // if (abs(meas.mag.y < IMU_TRASHOLD)) {
    //     meas.mag.y = 0;
    // }
    // if (abs(meas.mag.z < IMU_TRASHOLD)) {
    //     meas.mag.z = 0;
    // }

}


void GyroMagCalibration() {
    Serial.println("Starting Gyro calibration");
    int start_time = millis();
    int num_samples = 0;
    while (millis() - start_time < 10000) {
        IMU.read();
        mag.read();
        float x = IMU.g.x * POL_GYRO_SENS * deg2rad;
        float y = IMU.g.y * POL_GYRO_SENS * deg2rad;
        float z = IMU.g.z * POL_GYRO_SENS * deg2rad;
        num_samples++;
        meas.gyro_bias.x += (x - meas.gyro_bias.x) / num_samples;
        meas.gyro_bias.y += (y - meas.gyro_bias.y) / num_samples;
        meas.gyro_bias.z += (z - meas.gyro_bias.z) / num_samples;

        meas.mag_bias.x += (mag.m.x * POL_MAG_SENS - meas.mag_bias.x) / num_samples;
        meas.mag_bias.y += (mag.m.y * POL_MAG_SENS - meas.mag_bias.y) / num_samples;
        meas.mag_bias.z += (mag.m.z * POL_MAG_SENS - meas.mag_bias.z) / num_samples;

        meas.acc_bias.x += (IMU.a.x * POL_ACC_SENS - meas.acc_bias.x) / num_samples;
        meas.acc_bias.y += (IMU.a.y * POL_ACC_SENS - meas.acc_bias.y) / num_samples;
        meas.acc_bias.z += (IMU.a.z * POL_ACC_SENS - meas.acc_bias.z) / num_samples;
    }
    meas.initial_mag.x = meas.mag_bias.x;
    meas.initial_mag.y = meas.mag_bias.y;
    meas.initial_mag.z = meas.mag_bias.z;

    meas.initial_heading = atan2f(meas.initial_mag.y, meas.initial_mag.x);
    Serial.println("Finished Gyro calibration");
    delay(2000);
}

void IMU_init() {
    // Seting pins 24 and 25 to be used as I2C
    Wire.begin();
    Wire.setClock(420000);

    // Initialize IMU
    if (!IMU.init()) {
        Serial.println("Failed to detect and initialize IMU!");
        while (1);
    }
    if (!mag.init()) {
        Serial.println("Failed to detect and initialize Magnetometer!");
        while (1);
    }
    IMU.enableDefault();
    IMU.writeReg(LSM6::CTRL2_G, 0b01110000);   // ODR = 1040 Hz, FS = ±2000 dps
    IMU.writeReg(LSM6::CTRL1_XL, 0b01110000);  // ODR = 1040 Hz, FS = ±16g
    mag.enableDefault();
    mag.writeReg(LIS3MDL::CTRL_REG1, 0b11100110);  // ODR = 1000 Hz, high performance mode
    mag.writeReg(LIS3MDL::CTRL_REG2, 0x60);        // Full Scale = ±16 gauss
    Serial.println("calibarte the imu for high speed -");
}

