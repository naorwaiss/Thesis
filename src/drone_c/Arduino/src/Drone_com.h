#include "RTCom/RTCom.h"
#include "Var_types.h"
#include <Arduino.h>

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


#ifndef DRONE_COM_H
#define DRONE_COM_H

constexpr uint8_t SOCKET_IP_ADDRESS[] = {192, 168, 1, 199};
constexpr uint16_t SOCKET_PORT_NUMBER = 8888;
const RTComConfig SOCKET_CONFIG(1, 100, 200, 500);

namespace DRON_COM {

const SocketAddress SOCKET_ADDRESS = SocketAddress(SOCKET_IP_ADDRESS, SOCKET_PORT_NUMBER);
extern RTCom rtcomSocket;
extern RTComSession* socketSession;

extern Measurement_t meas;
extern quat_t q_est;
extern attitude_t desired_attitude;
extern motor_t motor_pwm;  // Currently not in use. replaced by PID_rate_out.PID_ret
extern attitude_t desired_rate;
extern attitude_t estimated_attitude;
extern attitude_t estimated_rate;
extern PID_out_t PID_stab_out;
extern PID_out_t PID_rate_out;
extern Controller_s controller_data;

void onConnection(RTComSession& session);
void init_com();
void emit_data();
void convert_Measurment_to_byte(Measurement_t meas,
                                quat_t q_est, attitude_t desired_attitude,
                                motor_t motor_pwm, attitude_t desired_rate,
                                attitude_t estimated_attitude, attitude_t estimated_rate,
                                PID_out_t PID_stab_out, PID_out_t PID_rate_out, Controller_s controller_data,
                                PID_const_t pid_load);
void send_data();

}  // namespace DRON_COM

#endif
