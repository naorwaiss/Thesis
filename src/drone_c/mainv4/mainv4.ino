#include <Arduino.h>
#include "Wire.h"
#include "src/Var_types.h"
#include "src/CompClass.h"
#include "src/Drone_com.h"
#include <LSM6.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include <AlfredoCRSF.h>
#include "src/MotorsControl.h"
#include "src/PID_type.h"

// IMU Data Conversion
#define POL_GYRO_SENS 8.75 / 1000.0f  // FS = 125
#define POL_ACC_SENS 0.061 / 1000.0f   // FS = 2g, 0.061 mg/LSB
#define POL_MAG_SENS 1 / 6842.0f

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

/*
------------------------------------------ Global Variables ------------------------------------------
*/

// ELRS Controller:
AlfredoCRSF crsf;
Controller_s controller_data;

// Motors Variables:
Motors motors(MOTOR1_PIN, MOTOR2_PIN, MOTOR3_PIN, MOTOR4_PIN);
bool is_armed = false;
bool is_armed_amit_flag = false;

// IMU and Filter Variables:
LSM6 IMU;
LIS3MDL mag;
LPS baro;

// Filter Object:
CompFilter Pololu_filter(true);  // True for enabling the magnetometer
float dt = 1 / 1100.0f;           // 1kHz sample rate in seconds

// Desired Attitude - From the controller:

Measurement_t meas;
quat_t q_est;
attitude_t desired_attitude;
motor_t motor_pwm;
attitude_t desired_rate;
attitude_t estimated_attitude;
attitude_t estimated_rate;
PID_out_t PID_stab_out;
PID_out_t PID_rate_out;

// timer//
elapsedMicros motor_timer;
elapsedMicros stab_timer;
const unsigned long STAB_PERIOD = 1000000 / (ESC_FREQUENCY / 2);  // 300 Hz period in microseconds
const unsigned long PWM_PERIOD_1 = 1000000 / ESC_FREQUENCY;       // 1,000,000 us / frequency in Hz

float t_PID_s = 0.0f;
float t_PID_r = 0.0f;

/*
------------------------------------------ Global Variables ------------------------------------------
*/

/*
------------------------------------------ Prototypes ------------------------------------------
*/

// Function prototypes
void Update_measurement();
void GyroMagCalibration();
void IMU_init();
void mapping_controller();
void check_arming_state();

void setup() {
    Serial.begin(115200);
    DRON_COM::init_com();
    IMU_init();

    // / activate crsf
    crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1);
    if (!crsfSerial) {
        while (1) {
            Serial.println("Invalid crsfSerial configuration");
        }
    }
    crsf.begin(crsfSerial);

    initializePIDParams();
    GyroMagCalibration();
    motors.Motors_init();
}

////////////////////////////////////////////////////////////////////////

void loop() {
    // Update ELRS data: Reading from the receiver and updating controller_data variable.
    update_controller();
    // Check arming:
    check_arming_state();
    // Update the measurement:
    Update_measurement();
    // Update the quaternion:
    Pololu_filter.UpdateQ(&meas, dt);
    // Get the Euler angles:
    Pololu_filter.GetEulerRPYdeg(&estimated_attitude, meas.initial_heading);
    // Get the quaternion:
    Pololu_filter.GetQuaternion(&q_est);

    if (is_armed) {
        // Get Actual rates:
        estimated_rate.roll = meas.gyro_LPF.x * rad2deg;
        estimated_rate.pitch = meas.gyro_LPF.y * rad2deg;
        estimated_rate.yaw = meas.gyro_LPF.z * rad2deg;

        if ((controller_data.aux1 > 1500) && (stab_timer >= STAB_PERIOD)) {  // Stabilize mode:
            // Calculating dt for the PID- in seconds:
            t_PID_s = (float)stab_timer / 1000000.0f;
            mapping_controller('s');
            Serial.println("stablize ");
            PID_stab_out = PID_stab(desired_attitude, estimated_attitude, t_PID_s);
            PID_stab_out.PID_ret.pitch = -1 * PID_stab_out.PID_ret.pitch;
            desired_rate = PID_stab_out.PID_ret;
            stab_timer = 0;
        } else if (controller_data.aux1 < 1500) {  // Acro mode:
            mapping_controller('r');
            Serial.println("acro ");
        }

        // Set the motor PWM:
        if ((controller_data.throttle > 1000) && (motor_timer >= PWM_PERIOD_1)) {
            t_PID_r = (float)motor_timer / 1000000.0f;
            PID_rate_out = PID_rate(desired_rate, estimated_rate, t_PID_r);
            motors.Motor_Mix(PID_rate_out.PID_ret, controller_data.throttle);
            motors.set_motorPWM();
            motor_timer = 0;
        }

        // Getting the motors struct to send data back:
        motor_pwm = motors.Get_motor();
    }
    // Sending new UDP Packet:
    DRON_COM::convert_Measurment_to_byte(meas,
                                         q_est, desired_attitude,
                                         motor_pwm, desired_rate,
                                         estimated_attitude, estimated_rate,
                                         PID_stab_out, PID_rate_out, controller_data);

    DRON_COM::send_data();

    Serial.print("roll ");
    Serial.println(estimated_attitude.roll);
    Serial.print("pitch ");
    Serial.println(estimated_attitude.pitch);

}

void Update_measurement() {
    // Read IMU data
    IMU.read();
    mag.read();
    meas.acc.x = IMU.a.x * POL_ACC_SENS;
    meas.acc.y = IMU.a.y * POL_ACC_SENS;
    meas.acc.z = IMU.a.z * POL_ACC_SENS;
    if (abs(meas.acc.x) < IMU_TRASHOLD) {
        meas.acc.x = 0;
    }
    if (abs(meas.acc.y) < IMU_TRASHOLD) {
        meas.acc.y = 0;
    }
    if (abs(meas.acc.z) < IMU_TRASHOLD) {
        meas.acc.z = 0;
    }

    meas.gyro.x = IMU.g.x * POL_GYRO_SENS * deg2rad - meas.gyro_bias.x;
    meas.gyro.y = IMU.g.y * POL_GYRO_SENS * deg2rad - meas.gyro_bias.y;
    meas.gyro.z = IMU.g.z * POL_GYRO_SENS * deg2rad - meas.gyro_bias.z;
    if (abs(meas.gyro.x) < IMU_TRASHOLD) {
        meas.gyro.x = 0;
    }
    if (abs(meas.gyro.y) < IMU_TRASHOLD) {
        meas.gyro.y = 0;
    }
    if (abs(meas.gyro.z) < IMU_TRASHOLD) {
        meas.gyro.z = 0;
    }
    meas.mag.x = mag.m.x * POL_MAG_SENS - meas.mag_bias.x;
    meas.mag.y = mag.m.y * POL_MAG_SENS - meas.mag_bias.y;
    meas.mag.z = mag.m.z * POL_MAG_SENS - meas.mag_bias.z;
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

void update_controller() {
    // Update the controller data:
    crsf.update();
    controller_data.throttle = crsf.getChannel(3);
    controller_data.throttle = map(controller_data.throttle, 988, 2012, 1000, 2000);
    controller_data.roll = crsf.getChannel(1);
    controller_data.pitch = crsf.getChannel(2);
    controller_data.yaw = crsf.getChannel(4);
    controller_data.aux1 = crsf.getChannel(5);
    controller_data.aux2 = crsf.getChannel(6);
    controller_data.aux3 = crsf.getChannel(7);
    controller_data.aux4 = crsf.getChannel(8);
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
    // calibrate the imu for fast

    // IMU.enableDefault();                       // 1.66 kHz, 2g, 245 dps
    // IMU.writeReg(LSM6::CTRL2_G, 0b10100000);   // 0b1010 for ODR 1.66 kHz, 0b0000 for 125 dps range
    // IMU.writeReg(LSM6::CTRL1_XL, 0b10100000);  // 0b1010 for ODR 1.66 kHz, 0b0000 for 2g range
    // mag.enableDefault();
    // mag.writeReg(LIS3MDL::CTRL_REG1, 0b11100110);  // 1 KHz, high performance mode
    // mag.writeReg(LIS3MDL::CTRL_REG2, 0x10);        // +- 4 gauss
    // Serial.println("calibarte the imu for high speed -");



    IMU.enableDefault();                       
    IMU.writeReg(LSM6::CTRL2_G,  0b01110000);  // ODR = 1040 Hz, FS = ±2000 dps
    IMU.writeReg(LSM6::CTRL1_XL, 0b01110000);  // ODR = 1040 Hz, FS = ±16g
    mag.enableDefault();
    mag.writeReg(LIS3MDL::CTRL_REG1, 0b11100110);  // ODR = 1000 Hz, high performance mode
    mag.writeReg(LIS3MDL::CTRL_REG2, 0x60);        // Full Scale = ±16 gauss
    baro.writeReg(0x20, 0b11000000);  // ODR = 1000 Hz, active mode
    Serial.println("calibarte the imu for high speed -");


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
        desired_rate.yaw = map(controller_data.yaw, CONTROLLER_MIN, CONTROLLER_MAX, MAX_RATE, -MAX_RATE);  // cahnge here
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
        if (is_armed_amit_flag == true || controller_data.throttle < (MOTOR_START + 100)) {
            is_armed = true;
            is_armed_amit_flag == true;
        }
    } else {  // Switch is in low position
        is_armed = false;
        is_armed_amit_flag == false;
        motors.Disarm();  // Ensure motors are stopped when disarmed
        Reset_PID();      // Reset PID states when disarmed
        resetMicrocontroller();
    }
}
