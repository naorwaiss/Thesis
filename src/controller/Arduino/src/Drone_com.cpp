#include "Drone_com.h"
#include <Arduino.h>
#include "RTCom/RTCom.h"

namespace ELRS_REMOTE {
RTCom rtcomSocket(SOCKET_ADDRESS, SOCKET_CONFIG);
RTComSession* socketSession = nullptr;
// int16_t rcChannels[CRSF_MAX_CHANNEL];
int16_t rcChannels[CRSF_MAX_CHANNEL];

uint8_t crsfPacket[CRSF_PACKET_SIZE];
float joyPacket[18];
mode current_mode = mode::STABLIZ;
ARM_STATE current_arm_state = ARM_STATE::DISARMED;

void onConnection(RTComSession& session) {
    Serial.printf("Session created with %s\r\n", session.address.toString());
    socketSession = &session;
    Serial.print("connect");
    session.on('j', [](const uint8_t* bytes, size_t size) {
        if (size != JOY_DATA) {
            Serial.print("size is not correct");
            return;
        }
        memcpy(joyPacket, bytes, size);
    });
}

void init_com() {
    SERIAL_PORT.begin(SERIAL_BAUDRATE);
    ELRS_REMOTE::rtcomSocket.begin();
    ELRS_REMOTE::rtcomSocket.onConnection(ELRS_REMOTE::onConnection);
}

void main_loop() {
    rtcomSocket.process();
    if (rtcomSocket.isSessionConnected(socketSession)) {
        m_and_s_crsf();
    }
    else{
        zeros_elers();
        m_and_s_crsf();
    
    }


    // Serial.print(rcChannels[4]);
}

// CRSF Implementation - making the packet
static uint8_t crsf_crc8tab[256] = {
    0x00, 0xD5, 0x7F, 0xAA, 0xFE, 0x2B, 0x81, 0x54, 0x29, 0xFC, 0x56, 0x83, 0xD7, 0x02, 0xA8, 0x7D,
    0x52, 0x87, 0x2D, 0xF8, 0xAC, 0x79, 0xD3, 0x06, 0x7B, 0xAE, 0x04, 0xD1, 0x85, 0x50, 0xFA, 0x2F,
    0xA4, 0x71, 0xDB, 0x0E, 0x5A, 0x8F, 0x25, 0xF0, 0x8D, 0x58, 0xF2, 0x27, 0x73, 0xA6, 0x0C, 0xD9,
    0xF6, 0x23, 0x89, 0x5C, 0x08, 0xDD, 0x77, 0xA2, 0xDF, 0x0A, 0xA0, 0x75, 0x21, 0xF4, 0x5E, 0x8B,
    0x9D, 0x48, 0xE2, 0x37, 0x63, 0xB6, 0x1C, 0xC9, 0xB4, 0x61, 0xCB, 0x1E, 0x4A, 0x9F, 0x35, 0xE0,
    0xCF, 0x1A, 0xB0, 0x65, 0x31, 0xE4, 0x4E, 0x9B, 0xE6, 0x33, 0x99, 0x4C, 0x18, 0xCD, 0x67, 0xB2,
    0x39, 0xEC, 0x46, 0x93, 0xC7, 0x12, 0xB8, 0x6D, 0x10, 0xC5, 0x6F, 0xBA, 0xEE, 0x3B, 0x91, 0x44,
    0x6B, 0xBE, 0x14, 0xC1, 0x95, 0x40, 0xEA, 0x3F, 0x42, 0x97, 0x3D, 0xE8, 0xBC, 0x69, 0xC3, 0x16,
    0xEF, 0x3A, 0x90, 0x45, 0x11, 0xC4, 0x6E, 0xBB, 0xC6, 0x13, 0xB9, 0x6C, 0x38, 0xED, 0x47, 0x92,
    0xBD, 0x68, 0xC2, 0x17, 0x43, 0x96, 0x3C, 0xE9, 0x94, 0x41, 0xEB, 0x3E, 0x6A, 0xBF, 0x15, 0xC0,
    0x4B, 0x9E, 0x34, 0xE1, 0xB5, 0x60, 0xCA, 0x1F, 0x62, 0xB7, 0x1D, 0xC8, 0x9C, 0x49, 0xE3, 0x36,
    0x19, 0xCC, 0x66, 0xB3, 0xE7, 0x32, 0x98, 0x4D, 0x30, 0xE5, 0x4F, 0x9A, 0xCE, 0x1B, 0xB1, 0x64,
    0x72, 0xA7, 0x0D, 0xD8, 0x8C, 0x59, 0xF3, 0x26, 0x5B, 0x8E, 0x24, 0xF1, 0xA5, 0x70, 0xDA, 0x0F,
    0x20, 0xF5, 0x5F, 0x8A, 0xDE, 0x0B, 0xA1, 0x74, 0x09, 0xDC, 0x76, 0xA3, 0xF7, 0x22, 0x88, 0x5D,
    0xD6, 0x03, 0xA9, 0x7C, 0x28, 0xFD, 0x57, 0x82, 0xFF, 0x2A, 0x80, 0x55, 0x01, 0xD4, 0x7E, 0xAB,
    0x84, 0x51, 0xFB, 0x2E, 0x7A, 0xAF, 0x05, 0xD0, 0xAD, 0x78, 0xD2, 0x07, 0x53, 0x86, 0x2C, 0xF9};

uint8_t crsf_crc8(const uint8_t* ptr, uint8_t len) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < len; i++) {
        crc = crsf_crc8tab[crc ^ *ptr++];
    }
    return crc;
}

void crsfPrepareDataPacket(uint8_t packet[], int16_t channels[]) {
    packet[0] = ELRS_ADDRESS;  // Header
    packet[1] = 24;            // length of type (24) + payload + crc
    packet[2] = TYPE_CHANNELS;
    packet[3] = (uint8_t)(channels[0] & 0x07FF);
    packet[4] = (uint8_t)((channels[0] & 0x07FF) >> 8 | (channels[1] & 0x07FF) << 3);
    packet[5] = (uint8_t)((channels[1] & 0x07FF) >> 5 | (channels[2] & 0x07FF) << 6);
    packet[6] = (uint8_t)((channels[2] & 0x07FF) >> 2);
    packet[7] = (uint8_t)((channels[2] & 0x07FF) >> 10 | (channels[3] & 0x07FF) << 1);
    packet[8] = (uint8_t)((channels[3] & 0x07FF) >> 7 | (channels[4] & 0x07FF) << 4);
    packet[9] = (uint8_t)((channels[4] & 0x07FF) >> 4 | (channels[5] & 0x07FF) << 7);
    packet[10] = (uint8_t)((channels[5] & 0x07FF) >> 1);
    packet[11] = (uint8_t)((channels[5] & 0x07FF) >> 9 | (channels[6] & 0x07FF) << 2);
    packet[12] = (uint8_t)((channels[6] & 0x07FF) >> 6 | (channels[7] & 0x07FF) << 5);
    packet[13] = (uint8_t)((channels[7] & 0x07FF) >> 3);
    packet[14] = (uint8_t)((channels[8] & 0x07FF));
    packet[15] = (uint8_t)((channels[8] & 0x07FF) >> 8 | (channels[9] & 0x07FF) << 3);
    packet[16] = (uint8_t)((channels[9] & 0x07FF) >> 5 | (channels[10] & 0x07FF) << 6);
    packet[17] = (uint8_t)((channels[10] & 0x07FF) >> 2);
    packet[18] = (uint8_t)((channels[10] & 0x07FF) >> 10 | (channels[11] & 0x07FF) << 1);
    packet[19] = (uint8_t)((channels[11] & 0x07FF) >> 7 | (channels[12] & 0x07FF) << 4);
    packet[20] = (uint8_t)((channels[12] & 0x07FF) >> 4 | (channels[13] & 0x07FF) << 7);
    packet[21] = (uint8_t)((channels[13] & 0x07FF) >> 1);
    packet[22] = (uint8_t)((channels[13] & 0x07FF) >> 9 | (channels[14] & 0x07FF) << 2);
    packet[23] = (uint8_t)((channels[14] & 0x07FF) >> 6 | (channels[15] & 0x07FF) << 5);
    packet[24] = (uint8_t)((channels[15] & 0x07FF) >> 3);

    packet[25] = crsf_crc8(&packet[2], packet[1] - 1);  // CRC
}

void crsfPrepareCmdPacket(uint8_t packetCmd[], uint8_t command, uint8_t value) {
    packetCmd[0] = ELRS_ADDRESS;
    packetCmd[1] = 6;  // length of Command (4) + payload + crc
    packetCmd[2] = TYPE_SETTINGS_WRITE;
    packetCmd[3] = ELRS_ADDRESS;
    packetCmd[4] = ADDR_RADIO;
    packetCmd[5] = command;
    packetCmd[6] = value;
    packetCmd[7] = crsf_crc8(&packetCmd[2], packetCmd[1] - 1);  // CRC
}

void CrsfWritePacket(uint8_t packet[], uint8_t packetLength) {
    SERIAL_PORT.write(packet, packetLength);
}

void byte_to_array(const uint8_t* bytes, float array[INCOMEING_AXIS]) {
    // Iterate through the bytes in chunks of 4 (size of a float)
    for (int i = 0; i < INCOMEING_AXIS; i++) {
        // Use memcpy to safely convert 4 bytes into a float
        memcpy(&array[i], &bytes[i * 4], sizeof(float));
    }
}

void zeros_elers() {
    for (uint8_t i = 0; i < CRSF_MAX_CHANNEL; i++) {
        joyPacket[i] = 0;
    }
}

void mixer() {
    bool mode1 = (joyPacket[16] > 0.7) ? true : false;
    bool mode2 = (joyPacket[17] > 0.7) ? true : false;
    bool arm_state = (joyPacket[6] > 0.7) && (joyPacket[10] > 0.7) ? true : false;
    bool disarm_state = (joyPacket[8] > 0.7) ? true : false;

    if (mode1) {
        current_mode = mode::STABLIZ;
    } else if (mode2) {
        current_mode = mode::ACRO;
    }

    if (arm_state) {
        current_arm_state = ARM_STATE::ARMED;
    } else if (disarm_state) {
        current_arm_state = ARM_STATE::DISARMED;
    }



}

void m_and_s_crsf() {
    mixer();

    rcChannels[0] = map(joyPacket[0]*-1, -1, 1, CRSF_DIGITAL_CHANNEL_MIN, CRSF_DIGITAL_CHANNEL_MAX);
    rcChannels[1] = map(joyPacket[1], -1, 1, CRSF_DIGITAL_CHANNEL_MIN, CRSF_DIGITAL_CHANNEL_MAX);
    rcChannels[3] = map(joyPacket[2]*-1, -1, 1, CRSF_DIGITAL_CHANNEL_MIN, CRSF_DIGITAL_CHANNEL_MAX);
    rcChannels[2] = map(joyPacket[3], -1, 1, CRSF_DIGITAL_CHANNEL_MIN, CRSF_DIGITAL_CHANNEL_MAX);
    rcChannels[4] = map(float(current_arm_state), 1, 2, CRSF_DIGITAL_CHANNEL_MIN, CRSF_DIGITAL_CHANNEL_MAX);
    rcChannels[5] = map(float(current_mode), 1, 2, CRSF_DIGITAL_CHANNEL_MIN, CRSF_DIGITAL_CHANNEL_MAX);

    for (size_t i = 0; i < 6; i++)
    {
        Serial.print(rcChannels[i]);
        Serial.print(" ");
    }
    Serial.println();
    

    crsfPrepareDataPacket(crsfPacket, rcChannels);
    SERIAL_PORT.write(crsfPacket, CRSF_PACKET_SIZE);
}

}  // namespace ELRS_REMOTE