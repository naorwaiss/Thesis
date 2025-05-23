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
#include "src/EkfClass.h"
#include "src/Madgwick.h"
#include "src/STD_Filter.h"
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
bool is_armed = false;
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
EKF ekf(&meas, DT);
Madgwick magwick_filter(&meas, &estimated_attitude,&q_est,833,0.9);
STD_Filter std_filter(&meas,833);


// timer//
elapsedMicros motor_timer;
elapsedMicros stab_timer;
elapsedMicros imu_timer;
elapsedMicros send_data_timer;

const unsigned long STAB_PERIOD = 1000000 / (ESC_FREQUENCY / 2);  // 300 Hz period in microseconds
const unsigned long PWM_PERIOD_1 = 1000000 / ESC_FREQUENCY;       // 1,000,000 us / frequency in Hz
const unsigned long IMU_PERIOD = 1000000 / SAMPLE_RATE;
const unsigned long SEND_DATA_PERIOD = 1000000 / 50;

double t_PID_s = 0.0f;
double t_PID_r = 0.0f;
float actual_dt = 0.0f;
int estimated_switch;

/*
------------------------------------------ Global Variables ------------------------------------------
*/

/*
------------------------------------------ Prototypes ------------------------------------------
*/

// Function prototypes
void GyroMagCalibration();
void IMU_init();
void mapping_controller(char);
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
    if (imu_timer >= IMU_PERIOD) {
        actual_dt = (double)imu_timer / 1000000.0f;
        Update_Measurement();
        // comp_filter.InitialFiltering(&meas);
        std_filter.all_filter();
        estimated_state_metude();

        if (is_armed) {
            // Get Actual rates:
            estimated_rate.roll = meas.gyro_LPF.x;
            estimated_rate.pitch = meas.gyro_LPF.y;
            estimated_rate.yaw = meas.gyro_LPF.z;

            if ((controller_data.aux1 > 1500) && (stab_timer >= STAB_PERIOD)) {  // Stabilize mode:
                // Calculating dt for the PID- in seconds:
                t_PID_s = (double)stab_timer / 1000000.0f;
                mapping_controller('s');
                // Serial.println("stablize ");
                PID_stab_out = PID_stab(desired_attitude, estimated_attitude, t_PID_s);
                PID_stab_out.PID_ret.pitch = -1 * PID_stab_out.PID_ret.pitch;
                desired_rate = PID_stab_out.PID_ret;
                desired_rate.yaw = map(controller_data.yaw, CONTROLLER_MIN, CONTROLLER_MAX, MAX_RATE, -MAX_RATE);
                stab_timer = 0;
            } else if (controller_data.aux1 < 1500) {  // Acro mode:
                mapping_controller('r');
                // Serial.println("acro ");
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

        if (send_data_timer >= SEND_DATA_PERIOD) {
            DRON_COM::convert_Measurment_to_byte(meas,
                                                 q_est, desired_attitude,
                                                 motor_pwm, desired_rate,
                                                 estimated_attitude, estimated_rate,
                                                 PID_stab_out, PID_rate_out, controller_data);

            DRON_COM::send_data();
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

    // meas.baro_data.pressure = baro.readPressureMillibars();
    // meas.baro_data.temperature = baro.readTemperatureC();
    // meas.baro_data.asl = baro.pressureToAltitudeMeters(meas.baro_data.pressure);
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
    delay(2000);
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

    IMU.enableDefault();                       // 1.66 kHz, 2g, 245 dps
    IMU.writeReg(LSM6::CTRL2_G, 0b01110100);   // 0b1010 for ODR 1.66 kHz, 0b0000 for 500 dps range
    IMU.writeReg(LSM6::CTRL1_XL, 0b01110010);  // 0b1010 for ODR 1.66 kHz, 0b0000 for 2g range with  ODR/10 filter
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

void mapping_controller(char state) {
    controller_trheshold();
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

void comclass_function() {
    comp_filter.UpdateQ(&meas, actual_dt / 2);
    comp_filter.GetEulerRPYdeg(&estimated_attitude, meas.initial_heading);
    comp_filter.GetQuaternion(&q_est);
}

void channel_estimated() {
    if (controller_data.aux4 > 1700) {
        estimated_switch = 0;
    } else if (controller_data.aux4 < 1100) {
        estimated_switch = 1;
    } else {
        estimated_switch = 2;
    }
}

void estimated_state_metude() {
    channel_estimated();
    switch (estimated_switch) {
        case 0:  // ekkf
            return ekf.run_kalman(&estimated_attitude, &q_est);
        case 1:  // compclass
            return comclass_function();
        case 2:
            return magwick_filter.madgwick_operation();
        default:
            return ekf.run_kalman(&estimated_attitude, &q_est);
    }
}