#include "HX711.h"
#include "src/RTCom/RTCom.h"

#define STOP_BUTTON_PIN 33

struct Motor {
    const int INA_PIN = 7;
    const int INB_PIN = 5;
    const int PWM_PIN = 6;
    void stopMotor() {
        analogWrite(PWM_PIN, 0);
        digitalWrite(INA_PIN, LOW);
        digitalWrite(INB_PIN, LOW);
    }
    void init_motor() {
        pinMode(INA_PIN, OUTPUT);
        pinMode(INB_PIN, OUTPUT);
        pinMode(PWM_PIN, OUTPUT);
    }
};

struct load_cell_t {
    const int DOUT = 8;
    const int CLK = 9;
    HX711 load_cell_intance;
    const float minTension = 35;
    const float maxTension = 40;
    const long rawEmpty = 162592;                             
    const float load_ScaleFactor = (200400 - rawEmpty) / 39;  
    float error = 0;
    long raw_Data;
    float tension;

    void error_find() {
        if (tension < minTension) {
            error = minTension - tension;  // צריך למתוח
        } else if (tension > maxTension) {
            error = maxTension - tension;  // צריך לשחרר
        } else {
            error = 0;
        }
    }
};

struct PID {
    float Kp = 10;
    float Ki = 0;
    float Kd = 0.5;
    float previousError = 0;
    float integral = 0;
    float integralMax = 1000;
    float control = 0;
};

load_cell_t load_cell;
Motor motor;
PID pid;
elapsedMicros loop_timer;
int hz_timer = 200;
const unsigned long micros_time = 1000000 / hz_timer;
constexpr uint8_t IP_ADDRESS[4] = {192, 168, 1, 177};
constexpr uint16_t PORT_NUMBER = 8888;
const SocketAddress SOCKET_ADDRESS = SocketAddress(IP_ADDRESS, PORT_NUMBER);
RTCom rtcomSocket(SOCKET_ADDRESS, RTComConfig(1, 100, 200, 500));
RTComSession *socketSession = nullptr;
uint8_t data[10];
uint8_t data_bytes[sizeof(float) * 2];

void onConnect(RTComSession &session) {
    socketSession = &session;
    Serial.print("Created session with ");
    Serial.println(socketSession->address.toString());
}

void onDisconnect(RTComSession &session) {
    socketSession = nullptr;
    Serial.print("Disconnected from ");
    Serial.println(session.address.toString());
}

void setup() {
    load_cell.load_cell_intance.begin(load_cell.DOUT, load_cell.CLK);
    analogWriteFrequency(motor.PWM_PIN, 20000);
    motor.init_motor();
    rtcomSocket.begin();
    rtcomSocket.onConnection(onConnect);
    pinMode(STOP_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(STOP_BUTTON_PIN) == LOW) {u
        motor.stopMotor();
        return;
    }
    if (loop_timer > micros_time) {
        // load_cell.raw_Data = load_cell.load_cell_intance.read();
        float raw_Data = load_cell.load_cell_intance.get_value();
        load_cell.tension = (raw_Data - load_cell.rawEmpty) / load_cell.load_ScaleFactor;  
        if (load_cell.tension > -2 && load_cell.tension < 2) load_cell.tension = 0;
        load_cell.error_find();
        pid.integral += load_cell.error * (1 / 200);
        pid.integral = constrain(pid.integral, -pid.integralMax, pid.integralMax);
        float derivative = (load_cell.error - pid.previousError) * hz_timer;
        pid.previousError = load_cell.error;
        pid.control = pid.Kp * load_cell.error + pid.Ki * pid.integral + pid.Kd * derivative;
        if (abs(pid.control) < 25) pid.control = 0;
        if (abs(load_cell.error) < 5) pid.control *= 0.5;
        applyMotorControl(pid.control);
        rtcomSocket.process();
        if (rtcomSocket.isSessionConnected(socketSession)) {
            sendDataToSocket();
        }
        loop_timer = 0;
    }
}

void applyMotorControl(float control) {
    int pwmOut = abs(pid.control);
    if (pwmOut < 50 && pwmOut > 0) pwmOut = 50;
    pwmOut = constrain(pwmOut, 0, 255);

    if (pid.control > 0) {
        digitalWrite(motor.INA_PIN, HIGH);
        digitalWrite(motor.INB_PIN, LOW);
        analogWrite(motor.PWM_PIN, pwmOut);
    } else if (pid.control < 0) {
        digitalWrite(motor.INA_PIN, LOW);
        digitalWrite(motor.INB_PIN, HIGH);
        analogWrite(motor.PWM_PIN, pwmOut);
    } else {
        motor.stopMotor();
    }
}

void sendDataToSocket() {
    float list[2];
    list[0] = load_cell.tension;
    list[1] = pid.control;
    memcpy(data_bytes, &list, sizeof(data_bytes));
    socketSession->emitTyped(data_bytes, sizeof(data_bytes), 'p');
}
