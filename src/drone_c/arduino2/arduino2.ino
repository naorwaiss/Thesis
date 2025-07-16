#include <Arduino.h>
#include "Wire.h"
#include "src/CompClass.h"
#include "src/IMU_type.h"
#include <AlfredoCRSF.h>
#include "src/MotorsControl.h"
#include "src/PID_type.h"
#include "src/EkfClass.h"
#include "src/STD_Filter.h"
#include "src/drone_comclass.h"
#include "src/Voltmeter.h"
#include "src/Var_types.h"
#include "src/drone_identify.h"

/*
------------------------------------------ Global Variables ------------------------------------------
*/

// ELRS Controller:
AlfredoCRSF ELRS;
Controller_s controller_data;

// Motors Variables:
Motors motors(MOTOR1_PIN, MOTOR2_PIN, MOTOR3_PIN, MOTOR4_PIN);

Measurement_t meas;
IMU_Func imu(&meas, SAMPLE_RATE);
drone_tune_t drone_tune;
CompFilter comp_filter(&drone_tune.filter_data); 
quat_t q_est;
attitude_t desired_attitude;
motor_t motor_pwm;
attitude_t desired_rate;
attitude_t estimated_attitude;
attitude_t estimated_rate;
PID_out_t PID_stab_out;
PID_out_t PID_rate_out;
Drone_Data_t drone_data_header;
// Voltmeter voltmeter(&drone_data_header, A3, A2, 69.441, 45.66, 0.0); //0.3
Voltmeter voltmeter(&drone_data_header, A3, A2); //0.3

Drone_com drone_com(&meas, &q_est, &desired_attitude, &motor_pwm,
                    &desired_rate, &estimated_attitude, &estimated_rate, &PID_stab_out, &PID_rate_out,
                    &controller_data, &drone_tune, &drone_data_header, &comp_filter);

elapsedMicros motor_timer;
elapsedMicros stab_timer;
elapsedMicros imu_timer;
elapsedMicros send_data_timer;
elapsedMicros estimated_filter_timer;



EKF ekf(&meas, 1 / SAMPLE_RATE);
STD_Filter std_filter(&meas, SAMPLE_RATE);

double t_PID_s = 0.0f;
double t_PID_r = 0.0f;
float actual_dt = 0.0f;

/*
------------------------------------------ Global Variables ------------------------------------------
*/


void setup() {
    Serial.begin(115200);
    drone_com.init_com();
    getbot_param(drone_tune, drone_data_header);
    imu.init_IMU(drone_data_header.acc_offset);
    voltmeter.init_voltmeter();


    ELRSSerial.begin(CRSF_BAUDRATE, SERIAL_8N1);
    if (!ELRSSerial) {
        while (1) {
            Serial.println("Invalid ELRSSerial configuration");
        }
    }
    ELRS.begin(ELRSSerial);
    setPID_params(&drone_tune.pid_const);
    comp_filter.set_beta(&drone_tune.filter_data);
    // imu.Initial_Calibration();
    motors.Motors_init();
}

////////////////////////////////////////////////////////////////////////

void loop() {
    // Update ELRS data: Reading from the receiver and updating controller_data variable.
    update_controller();
    check_arming_state();
    if (imu_timer >= IMU_PERIOD) {  /// rate loop
        actual_dt = (double)imu_timer / 1000000.0f;
        imu.Read_IMU();
        std_filter.all_filter();
        estimated_state_metude();
        voltmeter.read_bat_data();


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
                PID_stab_out = PID_stab(desired_attitude, estimated_attitude, t_PID_s);
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

void update_controller() {
    // Update the controller data:
    ELRS.update();
    controller_data.throttle = ELRS.getChannel(3);
    // controller_data.throttle = map(controller_data.throttle, 1000, 2000, 1000, 2000);
    controller_data.roll = ELRS.getChannel(1);
    controller_data.pitch = ELRS.getChannel(2);
    controller_data.yaw = ELRS.getChannel(4);
    controller_data.aux1 = ELRS.getChannel(5);
    controller_data.aux2 = ELRS.getChannel(6);
    controller_data.aux3 = ELRS.getChannel(7);
    controller_data.aux4 = ELRS.getChannel(8);
}

void controller_threshold() {
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
    controller_threshold();
    switch (drone_data_header.drone_mode)  // This switch statement is a placeholder for any specific conditions you might want to check.
    {
        case DroneMode::MODE_STABILIZE:
            desired_attitude.roll = map(controller_data.roll, CONTROLLER_MIN, CONTROLLER_MAX, -MAX_ANGLE, MAX_ANGLE);
            desired_attitude.pitch = map(controller_data.pitch, CONTROLLER_MIN, CONTROLLER_MAX, MAX_ANGLE, -MAX_ANGLE);
            desired_attitude.yaw = map(controller_data.yaw, CONTROLLER_MIN, CONTROLLER_MAX, MAX_ANGLE, -MAX_ANGLE);  // cahnge here
            break;
        case DroneMode::MODE_RATE:
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
    if (controller_data.aux2 > 1500) {  // Switch is in high position
        if ( controller_data.throttle < (MOTOR_START + 100)) {
            drone_data_header.is_armed = true;
        }
    } else {  // Switch is in low position
        drone_data_header.is_armed = false;
        motors.Disarm();  // Ensure motors are stopped when disarmed
        Reset_PID();      // Reset PID states when disarmed
        resetMicrocontroller();
    }
}

void channel_estimated() {
    if (controller_data.aux4 > 1700) {
        drone_data_header.filter_mode = DroneFilter::KALMAN;
    } else {
        drone_data_header.filter_mode = DroneFilter::COMPCLASS;
    }
}

void estimated_state_metude() {
    channel_estimated();
    switch (drone_data_header.filter_mode) {
        case DroneFilter::KALMAN:
            return ekf.run_kalman(&estimated_attitude, &q_est);
        case DroneFilter::COMPCLASS:
            comp_filter.UpdateQ(&meas.gyroRAD, &meas.acc, DT);
            comp_filter.GetEulerRPYdeg(&estimated_attitude);
            comp_filter.GetQuaternion(&q_est);  
            return;
        default:
            return ekf.run_kalman(&estimated_attitude, &q_est);
    }
}