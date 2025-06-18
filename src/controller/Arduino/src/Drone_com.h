#ifndef ELRS_REMOTE_H
#define ELRS_REMOTE_H

#include "RTCom/RTCom.h"

#include <Arduino.h>

#define CRSF_MAX_CHANNEL 16
#define CRSF_FRAME_SIZE_MAX 64
#define RADIO_ADDRESS 0xEA
#define ADDR_RADIO 0xEA  //  Radio Transmitter
#define TYPE_CHANNELS 0x16
#define CRSF_DIGITAL_CHANNEL_MIN 172
#define CRSF_DIGITAL_CHANNEL_MAX 1811
#define SERIAL_BAUDRATE 400000  /// rate for the tranciver s
#define CRSF_TIME_BETWEEN_FRAMES_US 1666
#define CRSF_PACKET_SIZE 26
#define ELRS_ADDRESS 0xEE
#define ELRS_PKT_RATE_COMMAND 0x01
#define ELRS_POWER_COMMAND 0x06
#define TYPE_SETTINGS_WRITE 0x2D
#define SERIAL_PORT Serial1
#define CRSF_PACKET_SIZE 26
#define ARRIVE_DATA 27
#define JOYSTICK "J"
#define JOY_DATA 72
#define INCOMEING_AXIS 8

////////////////////////////////////////////////////////////////////



enum class mode{
    STABLIZ =1,
    ACRO =2,
};

enum class ARM_STATE{
    DISARMED =1,
    ARMED =2,
};


constexpr uint8_t SOCKET_IP_ADDRESS[] = {192, 168, 1, 199};
constexpr uint16_t SOCKET_PORT_NUMBER = 8888;
const RTComConfig SOCKET_CONFIG(1, 100, 200, 500);

namespace ELRS_REMOTE {

const SocketAddress SOCKET_ADDRESS = SocketAddress(SOCKET_IP_ADDRESS, SOCKET_PORT_NUMBER);
extern RTCom rtcomSocket;
extern RTComSession *socketSession;

void onConnection(RTComSession &session);
void init_com();
void main_loop();
uint8_t crsf_crc8(const uint8_t *ptr, uint8_t len);
void crsfPrepareDataPacket(uint8_t packet[], int16_t channels[]);
void crsfPrepareCmdPacket(uint8_t packetCmd[], uint8_t command, uint8_t value);
void CrsfWritePacket(uint8_t packet[], uint8_t packetLength);
void zeros_elers();
void mixer();
void m_and_s_crsf();
}  // namespace ELRS_REMOTE

#endif
