#ifndef DRONE_COM_CLASS_H
#define DRONE_COM_CLASS_H

#include "RTCom/RTCom.h"
#include "Var_types.h"
#include <Arduino.h>
#include "PID_type.h"

#define MAG 'a'
#define P_IMU_RAW 'b'
#define P_IMU_FILTER 'c'
#define EUILER 'd'
#define RC 'e'
#define Quaternion_n 'f'
#define D_RATE 'g'
#define D_ATI 'h'
#define MOTOR_DATA_CONST 'i'
#define EST_RATE 'j'
#define PID_stab_prase 'k'
#define PID_rate_prase 'l'
#define PID_CONSTS_DATA 'm'
#define DRONE_SIGNATURE 'n'
#define PID_CONSTS_RETURN 'z'



class Drone_com {
   public:
    Drone_com(Measurement_t* meas, quat_t* q_est, attitude_t* desired_attitude, motor_t* motor_pwm, attitude_t* desired_rate, attitude_t* estimated_attitude, attitude_t* estimated_rate, PID_out_t* PID_stab_out, PID_out_t* PID_rate_out, Controller_s* controller_data, PID_const_t* pid_load, Drone_Data_t* drone_data_header);
    void init_com();
    void convert_Measurment_to_byte();
    void emit_data();
    void emit_pid_consts_feedback();
    void send_data();


   private:
    uint8_t SOCKET_IP_ADDRESS[4] = {192, 168, 1, 199};
    uint16_t SOCKET_PORT_NUMBER = 8888;
    RTComConfig SOCKET_CONFIG{1, 100, 200, 500};
    SocketAddress SOCKET_ADDRESS = SocketAddress(SOCKET_IP_ADDRESS, SOCKET_PORT_NUMBER);
    RTCom rtcomSocket;
    static RTComSession* socketSession;

    static Measurement_t* _meas;
    static quat_t* _q_est;
    static attitude_t* _desired_attitude;
    static motor_t* _motor_pwm;  // Currently not in use. replaced by PID_rate_out.PID_ret
    static attitude_t* _desired_rate;
    static attitude_t* _estimated_attitude;
    static attitude_t* _estimated_rate;
    static PID_out_t* _PID_stab_out;
    static PID_out_t* _PID_rate_out;
    static Controller_s* _controller_data;
    static PID_const_t* _pid_load;
    static Drone_Data_t* _drone_data_header;

    float* imu_data_raw = (float*)calloc(6, sizeof(float));
    uint8_t imu_byte_raw[sizeof(float) * 6];
    float* imu_data_filter = (float*)calloc(12, sizeof(float));
    uint8_t imu_byte_filter[sizeof(float) * 12];

    float* mag_data = (float*)calloc(3, sizeof(float));
    uint8_t mag_byte[sizeof(float) * 3];
    float* euler_data = (float*)calloc(3, sizeof(float));
    uint8_t euler_byte[sizeof(float) * 3];
    float* quaternion_data = (float*)calloc(4, sizeof(float));
    uint8_t quaternion_byte[sizeof(float) * 4];
    int* rc_ch_data = (int*)calloc(8, sizeof(int));
    uint8_t rc_byte[sizeof(int) * 8];
    float* desired_rate_data = (float*)calloc(3, sizeof(float));
    uint8_t desired_rate_byte[sizeof(float) * 3];
    float* desired_attitud_data = (float*)calloc(3, sizeof(float));
    uint8_t desired_attitud_byte[sizeof(float) * 3];
    float* estimated_attitude_data = (float*)calloc(3, sizeof(float));
    uint8_t estimated_attitude_byte[sizeof(float) * 3];
    float* estimated_rate_data = (float*)calloc(3, sizeof(float));
    uint8_t estimated_rate_byte[sizeof(float) * 3];
    float* PID_stab_out_data = (float*)calloc(15, sizeof(float));
    uint8_t PID_stab_out_byte[sizeof(float) * 15];
    float* PID_rate_data = (float*)calloc(15, sizeof(float));
    uint8_t PID_rate_byte[sizeof(float) * 15];
    float* motor_data = (float*)calloc(4, sizeof(float));
    uint8_t motor_pwm_byte[sizeof(float) * 4];
    float* pid_const_Data = (float*)calloc(15, sizeof(float));
    uint8_t pid_consts_byte[sizeof(float) * 15];
    uint8_t drone_header_byte[8];
    

    static void onConnection(RTComSession& session);
};

#endif
