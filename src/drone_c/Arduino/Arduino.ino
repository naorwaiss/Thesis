#include <Arduino.h>
#include "Wire.h"
#include "src/Var_types.h"
#include "src/CompClass.h"
// #include "src/Drone_com.h"
#include <LSM6.h>
#include <LIS3MDL.h>
#include <LPS.h>
#include <AlfredoCRSF.h>
#include "src/MotorsControl.h"
#include "src/PID_type.h"
#include "src/EkfClass.h"
#include "src/Madgwick.h"
#include "src/STD_Filter.h"
#include "src/drone_comclass.h"

// Define the global PID_CONSTS variable

// IMU Data Conversion
#define POL_GYRO_SENS 17.5 / 1000.0f  // FS = 125
#define POL_ACC_SENS 0.061 / 1000.0f  // FS = 2g, 0.061 mg/LSB
#define POL_MAG_SENS 1 / 6842.0f

#define crsfSerial Serial1  // Use Serial1 for the CRSF communication

// new drone
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

#define CONTROLL_THR_MAX 1520
#define CONTROLL_THR_MIN 1480

/*
------------------------------------------ Global Variables ------------------------------------------
*/

// ELRS Controller:
AlfredoCRSF crsf;
Controller_s controller_data;

// Motors Variables:
Motors motors(MOTOR1_PIN, MOTOR2_PIN, MOTOR3_PIN, MOTOR4_PIN);
bool THR_SAFE = false;

LSM6 IMU;
LIS3MDL mag;
LPS baro;
CompFilter comp_filter(false);  // True for enabling the magnetometer
float dt = 1 / 1100.0f;         // 1kHz sample rate in seconds
Measurement_t meas;
quat_t q_est;
attitude_t desired_attitude;
motor_t motor_pwm;
attitude_t desired_rate;
attitude_t estimated_attitude;
attitude_t estimated_rate;
PID_out_t PID_stab_out;
PID_out_t PID_rate_out;
PID_const_t PID_CONSTS;
Drone_Data_t drone_data_header;
Drone_com drone_com(&meas, &q_est, &desired_attitude, &motor_pwm, 
    &desired_rate, &estimated_attitude, &estimated_rate, &PID_stab_out, &PID_rate_out,
    &controller_data, &PID_CONSTS,&drone_data_header);

elapsedMicros motor_timer;
elapsedMicros stab_timer;
elapsedMicros imu_timer;
elapsedMicros send_data_timer;
elapsedMicros estimated_filter_timer;

const unsigned long STAB_PERIOD = 1000000 / STAB_FREQUENCY;  // 300 Hz period in microseconds
const unsigned long MOTOR_PERIOD = 1000000 / ESC_FREQUENCY;  // 1,000,000 us / frequency in Hz
const unsigned long IMU_PERIOD = 1000000 / SAMPLE_RATE;
const unsigned long SEND_DATA_PERIOD = 1000000 / 50; // 50 Hz

EKF ekf(&meas, 1 / STAB_FREQUENCY);
Madgwick magwick_filter(&meas, &estimated_attitude, &q_est, STAB_FREQUENCY, 0.8);
STD_Filter std_filter(&meas, SAMPLE_RATE);

double t_PID_s = 0.0f;
double t_PID_r = 0.0f;
float actual_dt = 0.0f;


/*
------------------------------------------ Global Variables ------------------------------------------
*/

/*
------------------------------------------ Prototypes ------------------------------------------
*/

// Function prototypes
void GyroMagCalibration();
void IMU_init();
void check_arming_state();

void setup() {
    Serial.begin(115200);
    drone_com.init_com();
    IMU_init();

    crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1);
    if (!crsfSerial) {
        while (1) {
            Serial.println("Invalid crsfSerial configuration");
        }
    }
    crsf.begin(crsfSerial);
    getbot_param(PID_CONSTS, drone_data_header);
    setPID_params(&PID_CONSTS);
    GyroMagCalibration();
    motors.Motors_init();
}

////////////////////////////////////////////////////////////////////////

void loop() {
    // Update ELRS data: Reading from the receiver and updating controller_data variable.
    update_controller();
    check_arming_state();
    if (imu_timer >= IMU_PERIOD) { /// rate loop
        actual_dt = (double)imu_timer / 1000000.0f;
        Update_Measurement();
        std_filter.all_filter();

        if (estimated_filter_timer >= STAB_PERIOD) {
            //estimated the state even if the drone is not armed
            estimated_state_metude();
            estimated_filter_timer = 0;
        }

        if (drone_data_header.is_armed) {
            // Get Actual rates:
            estimated_rate.roll = meas.gyroDEG.x;
            estimated_rate.pitch = meas.gyroDEG.y;
            estimated_rate.yaw = meas.gyroDEG.z;

            if ((controller_data.aux1 > 1500) && (stab_timer >= STAB_PERIOD)) {  // Stabilize mode:
                // Calculating dt for the PID- in seconds:
                t_PID_s = (double)stab_timer / 1000000.0f;
                drone_data_header.drone_mode = DroneMode::MODE_STABILIZE;
                mapping_controller();
                PID_stab_out = PID_stab(desired_attitude, estimated_attitude, estimated_rate, t_PID_s);
                PID_stab_out.PID_ret.pitch = -1 * PID_stab_out.PID_ret.pitch;
                desired_rate = PID_stab_out.PID_ret;
                desired_rate.yaw = map(controller_data.yaw, CONTROLLER_MIN, CONTROLLER_MAX, MAX_RATE, -MAX_RATE);
                stab_timer = 0;
            } else if (controller_data.aux1 < 1500) {  // Acro mode:
                drone_data_header.drone_mode = DroneMode::MODE_RATE;
                mapping_controller();
            }
            if ((controller_data.throttle > 1000) && (motor_timer >= MOTOR_PERIOD)) {
                t_PID_r = (float)motor_timer / 1000000.0f;
                PID_rate_out = PID_rate(desired_rate, estimated_rate, t_PID_r);
                motors.Motor_Mix(PID_rate_out.PID_ret, controller_data.throttle);
                motors.set_motorPWM();
                motor_timer = 0;
            }

            // Getting the motors struct to send data back:
            motor_pwm = motors.Get_motor();
        }

        if (send_data_timer >= SEND_DATA_PERIOD) {
            drone_com.convert_Measurment_to_byte();
            drone_com.send_data();
            send_data_timer = 0;
        }
        imu_timer = 0;
    }
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

    meas.gyroDEG.x = IMU.g.x * POL_GYRO_SENS - meas.gyro_bias.x;
    meas.gyroDEG.y = IMU.g.y * POL_GYRO_SENS - meas.gyro_bias.y;
    meas.gyroDEG.z = IMU.g.z * POL_GYRO_SENS - meas.gyro_bias.z;
    meas.gyroRAD.x = meas.gyroDEG.x * deg2rad;
    meas.gyroRAD.y = meas.gyroDEG.y * deg2rad;
    meas.gyroRAD.z = meas.gyroDEG.z * deg2rad;

    meas.mag.x = mag.m.x * POL_MAG_SENS - meas.mag_bias.x;
    meas.mag.y = mag.m.y * POL_MAG_SENS - meas.mag_bias.y;
    meas.mag.z = mag.m.z * POL_MAG_SENS - meas.mag_bias.z;
    if (abs(meas.mag.x < IMU_THRESHOLD)) {
        meas.mag.x = 0;
    }
    if (abs(meas.mag.y < IMU_THRESHOLD)) {
        meas.mag.y = 0;
    }
    if (abs(meas.mag.z < IMU_THRESHOLD)) {
        meas.mag.z = 0;
    }
}

void GyroMagCalibration() {
    Serial.println("Starting Gyro calibration");
    int start_time = millis();
    int num_samples = 0;
    while (millis() - start_time < 10000) {
        IMU.read();
        mag.read();
        float x = IMU.g.x * POL_GYRO_SENS;
        float y = IMU.g.y * POL_GYRO_SENS;
        float z = IMU.g.z * POL_GYRO_SENS;
        num_samples++;
        meas.gyro_bias.x += (x - meas.gyro_bias.x) / num_samples;
        meas.gyro_bias.y += (y - meas.gyro_bias.y) / num_samples;
        meas.gyro_bias.z += (z - meas.gyro_bias.z) / num_samples;
        meas.acc_bias.x += (IMU.a.x * POL_ACC_SENS - meas.acc_bias.x) / num_samples;
        meas.acc_bias.y += (IMU.a.y * POL_ACC_SENS - meas.acc_bias.y) / num_samples;
    }
    meas.initial_mag.x = meas.mag_bias.x;
    meas.initial_mag.y = meas.mag_bias.y;
    meas.initial_mag.z = meas.mag_bias.z;
    meas.initial_heading = atan2f(meas.initial_mag.y, meas.initial_mag.x);

    // meas.acc_bias.z += 1.0f; //  Adding back 1g, so the bias will remove only noise around 1g.

    Serial.println("Finished Gyro calibration");
    delay(1000);
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

    IMU.enableDefault();  // 1.66 kHz, 2g, 245 dps
    // These configurations are based on tables 44,45,47,48 in the datasheet https://www.pololu.com/file/0J1899/lsm6dso.pdf
    IMU.writeReg(LSM6::CTRL2_G, 0b01110000);  
    IMU.writeReg(LSM6::CTRL4_C, 0b00000010); // Enabaling the LPF for Gyro
    IMU.writeReg(LSM6::CTRL6_C, 0b00001110);  // Gyro LPF cutoff frequency 25Hz

    IMU.writeReg(LSM6::CTRL1_XL, 0b01110000);  // Setting the ACC to 833Hz and 2g FS
    IMU.writeReg(LSM6::CTRL8_XL, 0b01101000); // Enabaling LPF and cutoff at 18.5 Hz - ODR/45

    mag.enableDefault();
    mag.writeReg(LIS3MDL::CTRL_REG1, 0b11111010);  // 1 KHz, high performance mode
    mag.writeReg(LIS3MDL::CTRL_REG2, 0x10);        // +- 4 gauss
}

void controller_trheshold() {
    if ((controller_data.roll <= CONTROLL_THR_MAX) && (controller_data.roll >= CONTROLL_THR_MIN)) {
        controller_data.roll = 1500;
    }
    if ((controller_data.pitch <= CONTROLL_THR_MAX) && (controller_data.pitch >= CONTROLL_THR_MIN)) {
        controller_data.pitch = 1500;
    }
    if ((controller_data.yaw <= CONTROLL_THR_MAX) && (controller_data.yaw >= CONTROLL_THR_MIN)) {
        controller_data.yaw = 1500;
    }
}

void mapping_controller() {
    controller_trheshold();
    switch (drone_data_header.drone_mode)  // This switch statement is a placeholder for any specific conditions you might want to check.
    {
    case DroneMode::MODE_STABILIZE:
        Serial.println("stablize");
        desired_attitude.roll = map(controller_data.roll, CONTROLLER_MIN, CONTROLLER_MAX, -MAX_ANGLE, MAX_ANGLE);
        desired_attitude.pitch = map(controller_data.pitch, CONTROLLER_MIN, CONTROLLER_MAX, MAX_ANGLE, -MAX_ANGLE);
        desired_attitude.yaw = map(controller_data.yaw, CONTROLLER_MIN, CONTROLLER_MAX, MAX_ANGLE, -MAX_ANGLE);  // cahnge here
        break;
    case DroneMode::MODE_RATE:
        Serial.println("rate");
        desired_rate.roll = map(controller_data.roll, CONTROLLER_MIN, CONTROLLER_MAX, -MAX_RATE, MAX_RATE);
        desired_rate.pitch = map(controller_data.pitch, CONTROLLER_MIN, CONTROLLER_MAX, -MAX_RATE, MAX_RATE);
        desired_rate.yaw = map(controller_data.yaw, CONTROLLER_MIN, CONTROLLER_MAX, MAX_RATE, -MAX_RATE);
        break;
    
    default:
        break;
    }
}

void resetMicrocontroller() {
    // Trigger a software reset
    if (controller_data.aux3 > 1700) {
        Serial.println(" reset ");
        SCB_AIRCR = 0x05FA0004;
    }
}

void check_arming_state() {
    /// need to check it
    // Using aux2 (channel 6) as the arming switch
    // You can change this to any aux channel you prefer
    if (controller_data.aux2 > 1500) {  // Switch is in high position
        if (THR_SAFE == true || controller_data.throttle < (MOTOR_START + 100)) {
            drone_data_header.is_armed = true;
            THR_SAFE == true;
        }
    } else {  // Switch is in low position
        drone_data_header.is_armed = false;
        THR_SAFE == false;
        motors.Disarm();  // Ensure motors are stopped when disarmed
        Reset_PID();      // Reset PID states when disarmed
        resetMicrocontroller();
    }
}

void comclass_function() {
    comp_filter.UpdateQ(&meas, DT);
    comp_filter.GetEulerRPYdeg(&estimated_attitude, meas.initial_heading);
    comp_filter.GetQuaternion(&q_est);
}

void channel_estimated() {
    if (controller_data.aux4 > 1700) {
        drone_data_header.filter_mode = DroneFilter::KALMAN;
    } else if (controller_data.aux4 < 1100) {
        drone_data_header.filter_mode = DroneFilter::COMPCLASS;
    } else {
        drone_data_header.filter_mode = DroneFilter::MADGWICK;
    }
}

void estimated_state_metude() {
    channel_estimated();
    switch (drone_data_header.filter_mode) {
        case DroneFilter::KALMAN:
            Serial.println("ekf");
            return ekf.run_kalman(&estimated_attitude, &q_est);
        case DroneFilter::COMPCLASS:
            Serial.println("compclass");
            return comclass_function();
        case DroneFilter::MADGWICK:
            Serial.println("magwick");
            return magwick_filter.madgwick_operation();
        default:
            return ekf.run_kalman(&estimated_attitude, &q_est);
    }
}