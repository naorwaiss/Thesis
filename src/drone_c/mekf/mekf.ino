#include <LSM6.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include "eigen.h"
#include <Eigen/LU>
#include "src/Var_types.h"
#include "src/EkfClass.h"
#include "src/MotorsControl.h"
#include <AlfredoCRSF.h>
#include "src/Drone_com.h"
#include "src/PID_type.h"

#define POL_ACC_SENS 0.061 / 1000.0f  // FS = 2g, 0.061 mg/LSB
#define POL_MAG_SENS 1 / 6842.0f
#define POL_GYRO_SENS 8.75f / 1000.0f
#define IMU_TRASHOLD 0.04
#define IMU_THRESHOLD 0.05f

#define crsfSerial Serial1  // Use Serial1 for the CRSF communication

#define MOTOR1_PIN 2  // front right
#define MOTOR2_PIN 3  // back right
#define MOTOR3_PIN 4  // back left
#define MOTOR4_PIN 5  // fron left
// new drone

#define MAX_ANGLE 10.0f
#define MAX_RATE 200.0f
#define CONTROLLER_MIN 988
#define CONTROLLER_MAX 2012
#define IMU_THRESHOLD 0.05f

LSM6 IMU;
LIS3MDL mag;
LPS baro;
Measurement_t meas;
EKF ekf(&meas, DT);
attitude_t estimated_attitude;
quat_t q_est;
motor_t motor_pwm;
attitude_t desired_rate;
attitude_t estimated_rate;
attitude_t desired_attitude;
PID_out_t PID_stab_out;
PID_out_t PID_rate_out;
AlfredoCRSF crsf;
Controller_s controller_data;
Motors motors(MOTOR1_PIN, MOTOR2_PIN, MOTOR3_PIN, MOTOR4_PIN);
bool is_armed = false;
bool THR_SAFE = false;

elapsedMicros motor_timer;
elapsedMicros stab_timer;
elapsedMicros imu_timer;
elapsedMicros send_data_timer;

const unsigned long STAB_PERIOD = 1000000 / (ESC_FREQUENCY / 2);  // 300 Hz period in microseconds
const unsigned long PWM_PERIOD_1 = 1000000 / ESC_FREQUENCY;       // 1,000,000 us / frequency in Hz
const unsigned long IMU_PERIOD = 1000000 / SAMPLE_RATE;
const unsigned long SEND_DATA_PERIOD = 1000000 / 50;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    DRON_COM::init_com();
    IMU_init();
    // Serial.println("IMU ready with 2D Kalman");
    // crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1);
    // if (!crsfSerial) {
    //     while (1) {
    //         Serial.println("Invalid crsfSerial configuration");
    //     }
    // }
    // crsf.begin(crsfSerial);
    // initializePIDParams();
    // motors.Motors_init();
}

void loop() {
    // update_controller();
    // check_arming_state();

    if (imu_timer >= IMU_PERIOD) {
        Update_Measurement();
        ekf.run_kalman(&estimated_attitude, &q_est);

        Serial.print("the data return");
        Serial.print(estimated_attitude.pitch);Serial.print(" ");
        Serial.print(estimated_attitude.roll);Serial.print(" ");
        Serial.print(estimated_attitude.yaw);Serial.println(" ");




        imu_timer = 0;
    }
    delay(1);
}

void IMU_init() {
    Wire.begin();
    Wire.setClock(420000);
    if (!IMU.init()) {
        Serial.println("Failed to detect and initialize IMU!");
        while (1);
    }
    if (!mag.init()) {
        Serial.println("Failed to detect and initialize Magnetometer!");
        while (1);
    }
    IMU.enableDefault();                       // 1.66 kHz, 2g, 245 dps
    IMU.writeReg(LSM6::CTRL2_G, 0b01110100);   // 0b1010 for ODR 1.66 kHz, 0b0000 for 500 dps range
    IMU.writeReg(LSM6::CTRL1_XL, 0b01110010);  // 0b1010 for ODR 1.66 kHz, 0b0000 for 2g range with  ODR/10 filter
    mag.enableDefault();
    mag.writeReg(LIS3MDL::CTRL_REG1, 0b11111010);  // 1 KHz, high performance mode
    mag.writeReg(LIS3MDL::CTRL_REG2, 0x10);        // +- 4 gauss
}

void Update_Measurement() {
    // Read IMU data
    IMU.read();
    mag.read();
    meas.acc.x = IMU.a.x * POL_ACC_SENS - meas.acc_bias.x;
    meas.acc.y = IMU.a.y * POL_ACC_SENS - meas.acc_bias.y;
    meas.acc.z = IMU.a.z * POL_ACC_SENS - meas.acc_bias.z;
    if (abs(meas.acc.x) < IMU_THRESHOLD) {
        meas.acc.x = 0;
    }
    if (abs(meas.acc.y) < IMU_THRESHOLD) {
        meas.acc.y = 0;
    }
    if (abs(meas.acc.z) < IMU_THRESHOLD) {
        meas.acc.z = 0;
    }

    meas.gyroDEG.x = IMU.g.x * POL_GYRO_SENS - meas.gyro_bias.x;  // raw data gyro
    meas.gyroDEG.y = IMU.g.y * POL_GYRO_SENS - meas.gyro_bias.y;  // raw data gyro
    meas.gyroDEG.z = IMU.g.z * POL_GYRO_SENS - meas.gyro_bias.z;  // raw data gyro
    if (abs(meas.gyroDEG.x) < IMU_THRESHOLD) {
        meas.gyroDEG.x = 0;
    }
    if (abs(meas.gyroDEG.y) < IMU_THRESHOLD) {
        meas.gyroDEG.y = 0;
    }
    if (abs(meas.gyroDEG.z) < IMU_THRESHOLD) {
        meas.gyroDEG.z = 0;
    }
    meas.gyroRAD.x = meas.gyroDEG.x * deg2rad;
    meas.gyroRAD.y = meas.gyroDEG.y * deg2rad;
    meas.gyroRAD.z = meas.gyroDEG.z * deg2rad;

    meas.mag.x = mag.m.x * POL_MAG_SENS - meas.mag_bias.x;
    meas.mag.y = mag.m.y * POL_MAG_SENS - meas.mag_bias.y;
    meas.mag.z = mag.m.z * POL_MAG_SENS - meas.mag_bias.z;

    Serial.print(" mag read ");
    Serial.print(meas.mag.x); Serial.print("  ");
    Serial.print(meas.mag.y); Serial.print("  ");
    Serial.print(meas.mag.z); Serial.println("  ");

}

void mapping_controller(char state) {
    if (state == 's') {  // Mapping the controller input into desired angle:
        desired_attitude.roll = map(controller_data.roll, CONTROLLER_MIN, CONTROLLER_MAX, -MAX_ANGLE, MAX_ANGLE);
        desired_attitude.pitch = map(controller_data.pitch, CONTROLLER_MIN, CONTROLLER_MAX, MAX_ANGLE, -MAX_ANGLE);
        desired_attitude.yaw = map(controller_data.yaw, CONTROLLER_MIN, CONTROLLER_MAX, MAX_ANGLE, -MAX_ANGLE);  // cahnge here
        /// neeed to remove or change the constrain here -> not limit the yaw
    } else if (state == 'r') {  // Mapping the controller input into desired rate:
        desired_rate.roll = map(controller_data.roll, CONTROLLER_MIN, CONTROLLER_MAX, -MAX_RATE, MAX_RATE);
        desired_rate.pitch = map(controller_data.pitch, CONTROLLER_MIN, CONTROLLER_MAX, -MAX_RATE, MAX_RATE);
        desired_rate.yaw = map(controller_data.yaw, CONTROLLER_MIN, CONTROLLER_MAX, MAX_RATE, -MAX_RATE);
    }
}

void resetMicrocontroller() {
    // Trigger a software reset
    if (controller_data.aux3 > 1500) {
        SCB_AIRCR = 0x05FA0004;
        Serial.println(" reset ");
    }
}

void check_arming_state() {
    /// need to check it
    // Using aux2 (channel 6) as the arming switch
    // You can change this to any aux channel you prefer
    if (controller_data.aux2 > 1500) {  // Switch is in high position
        if (THR_SAFE == true || controller_data.throttle < (MOTOR_START + 100)) {
            is_armed = true;
            THR_SAFE == true;
        }
    } else {  // Switch is in low position
        is_armed = false;
        THR_SAFE == false;
        motors.Disarm();  // Ensure motors are stopped when disarmed
        Reset_PID();      // Reset PID states when disarmed
        resetMicrocontroller();
    }
}

void update_controller() {
    // Update the controller data:
    crsf.update();
    controller_data.throttle = crsf.getChannel(3);
    // controller_data.throttle = map(controller_data.throttle, 1000, 2000, 1000, 2000);
    controller_data.roll = crsf.getChannel(1);
    controller_data.pitch = crsf.getChannel(2);
    controller_data.yaw = crsf.getChannel(4);
    controller_data.aux1 = crsf.getChannel(5);
    controller_data.aux2 = crsf.getChannel(6);
    controller_data.aux3 = crsf.getChannel(7);
    controller_data.aux4 = crsf.getChannel(8);
}