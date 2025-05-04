#include "lidar_class.h"


lidar_data* lidar_class::measurement = nullptr;  // Pointer to the measurement data
RTComSession* lidar_class::socketSession = nullptr;

lidar_class::lidar_class(lidar_data* data, RTComSession* Session, HardwareSerial* Serial, int* motor_pin) {
    // Constructor implementation
    // Initialize the lidar_class with the provided data structure
    measurement = data;
    socketSession = Session;
    lidarSerial = Serial;   
    pin = motor_pin;
}

void lidar_class::updateSession(RTComSession* newSession) {
    socketSession = newSession;
}

void lidar_class::sendStartScan() {
    uint8_t start_scan[] = {0xA5, 0x20};
    lidarSerial->write(start_scan, sizeof(start_scan));
}

void lidar_class::send_lidar_data() {
    if (socketSession == nullptr) {
        Serial.println(" The sockerSession is nullptr at Sender");
        return;
    }
    memcpy(lidar_data_byte, &measurement->angle, sizeof(float));
    memcpy(lidar_data_byte + sizeof(float), &measurement->distance, sizeof(float));
    socketSession->emitTyped(lidar_data_byte, sizeof(lidar_data_byte), "L");
}

void lidar_class::init_lidar() {
    lidarSerial->begin(115200);
    delay(1000);
    pinMode(*pin, OUTPUT);
    digitalWrite(*pin, HIGH);
    sendStartScan();
    Serial.println("Started scanning...");
}

void lidar_class::take_lidar_data() {
        if (lidarSerial->available() >= 5 && lidar_timer >= 100000) {  // 100000 us = 100 ms
        uint8_t b[5];
        lidarSerial->readBytes(b, 5);

        if ((b[0] & 0x01) && !(b[0] & 0x02)) {
            uint16_t angle_raw = ((b[3]) | (b[4] << 8)) >> 1;
            float angle = angle_raw / 64.0;

            uint16_t dist_raw = b[1] | (b[2] << 8);
            float distance = (dist_raw / 4.0)/1000.0;  // Convert to mm

            measurement->angle = angle;
            measurement->distance = distance;

            lidar_timer = 0;  // Reset timer after each print
            send_lidar_data();
        }
    }
}

