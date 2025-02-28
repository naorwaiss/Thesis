#include "RTCom/RTCom.h"
#include "Var_types.h"

#include <Arduino.h>


#define MAG 'm'
#define P_IMU_RAW 'p'
#define P_IMU_FILTER 'P'
#define EUILER 'e'
#define RC 'r'
#define Quaternion 'q'
#define D_RATE 'z'
#define D_ATI 'w'
#define MOTOR_DATA_CONST 'a'
#define EST_RATE 'n'
#define PID_stab_prase 'l'
#define PID_rate_prase 'b'




#ifndef DRONE_COM_H
#define DRONE_COM_H

constexpr uint8_t SOCKET_IP_ADDRESS[] = {192, 168, 1, 199};
constexpr uint16_t SOCKET_PORT_NUMBER = 8888;
const RTComConfig SOCKET_CONFIG(1, 100, 200, 500);




namespace DRON_COM {

const SocketAddress SOCKET_ADDRESS = SocketAddress(SOCKET_IP_ADDRESS, SOCKET_PORT_NUMBER);
extern RTCom rtcomSocket;
extern RTComSession *socketSession;

extern Measurement_t meas;
extern quat_t q_est;
extern attitude_t desired_attitude;
extern attitude_t desired_rate;
extern attitude_t estimated_attitude;
extern attitude_t estimated_rate;





void onConnection(RTComSession& session);
void init_com();
void emit_data();
void convert_Measurment_to_byte(Measurement_t meas,
                                quat_t q_est, attitude_t euiler);
void send_data();

}

#endif

