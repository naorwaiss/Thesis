#include <Arduino.h>
#include "src/lidar_class.h"

// Serial1: RX = pin 0 (RPLIDAR TX)
#define MOTOR_CONTROL_PIN 2
int motor_pin = MOTOR_CONTROL_PIN;
elapsedMicros print_timer;  // Timer for 10Hz control

constexpr uint8_t SOCKET_IP_ADDRESS[] = {192, 168, 1, 178};
constexpr uint16_t SOCKET_PORT_NUMBER = 8888;
const RTComConfig SOCKET_CONFIG(1, 100, 200, 500);
const SocketAddress SOCKET_ADDRESS = SocketAddress(SOCKET_IP_ADDRESS, SOCKET_PORT_NUMBER);

RTCom rtcomSocket(SOCKET_ADDRESS, SOCKET_CONFIG);
RTComSession *socketSession = nullptr;

lidar_data output;
lidar_class lidar(&output, socketSession, &Serial1, &motor_pin);

void onConnect(RTComSession &session) {
    socketSession = &session;
    lidar.updateSession(socketSession);
    Serial.println("Connected to Spider.");
    session.onDisconnect([]() {
        Serial.println("Disconnected from Spider.");
    });   
}

void setup() {
    lidar.init_lidar();
    rtcomSocket.begin();
    rtcomSocket.onConnection(onConnect);
}

void loop() {
    lidar.take_lidar_data();
    // rtcomSocket.process();
    Serial.println("Lidar data sent.");
    Serial.print("Angle: ");
    Serial.print(output.angle);
    Serial.print(" Distance: ");
    Serial.println(output.distance);
    
    // if (!rtcomSocket.isSessionConnected(socketSession)) {
    //     return;
    // }
    
}
