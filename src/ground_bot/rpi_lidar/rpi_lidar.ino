#include <Arduino.h>
#include "lidar_class.h"

// Serial1: RX = pin 0 (RPLIDAR TX)
#define RPLIDAR_SERIAL Serial1
#define MOTOR_CONTROL_PIN 2

elapsedMicros print_timer;  // Timer for 10Hz control

void sendStartScan() {
    uint8_t start_scan[] = {0xA5, 0x20};
    RPLIDAR_SERIAL.write(start_scan, sizeof(start_scan));
}

void setup() {
    Serial.begin(115200);          // USB Serial to PC
    RPLIDAR_SERIAL.begin(115200);  // LIDAR default baudrate
    pinMode(MOTOR_CONTROL_PIN, OUTPUT);
    digitalWrite(MOTOR_CONTROL_PIN, HIGH);  // Start motor
    delay(1000);
    sendStartScan();
    Serial.println("Started scanning...");
}

void loop() {
    if (RPLIDAR_SERIAL.available() >= 5 && print_timer >= 100000) {  // 100000 us = 100 ms
        uint8_t b[5];
        RPLIDAR_SERIAL.readBytes(b, 5);

        // Check start flags: bit 0 == 1, bit 1 == 0
        if ((b[0] & 0x01) && !(b[0] & 0x02)) {
            uint16_t angle_raw = ((b[3]) | (b[4] << 8)) >> 1;
            float angle = angle_raw / 64.0;

            uint16_t dist_raw = b[1] | (b[2] << 8);
            float distance = (dist_raw / 4.0)/1000.0;  // Convert to mm

            Serial.print("Angle: ");
            Serial.print(angle, 2);
            Serial.print("°, Distance: ");
            Serial.print(distance, 5);
            Serial.println(" m");

            print_timer = 0;  // Reset timer after each print
        }
    }
}
