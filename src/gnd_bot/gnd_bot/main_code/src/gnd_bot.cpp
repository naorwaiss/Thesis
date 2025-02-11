#include "gnd_bot.h"

namespace G_BOT {

RTCom rtcomSocket(SOCKET_ADDRESS, SOCKET_CONFIG);
RTComSession *socketSession = nullptr;

AlfredoCRSF crsf;

////// global varible//////
uint16_t channels[NUM_CHANNELS];  // RC channel values
long encoder_position_left;
long encoder_position_right;
double delta_t = 0;
unsigned long curent_timer = 0;
unsigned long global_time = 0;

Motor_Data right_motor = {
    .pwmh_pin = 3,
    .dir_pin = 2,
    .encoderA_pin = 7,
    .encoderB_pin = 6,
};

Motor_Data left_motor = {
    .pwmh_pin = 5,
    .dir_pin = 4,
    .encoderA_pin = 8,
    .encoderB_pin = 9,
};

Encoder Enc_right(right_motor.encoderA_pin, right_motor.encoderB_pin);  // Channel A -> pin 7, Channel B -> pin 8
Encoder Enc_left(left_motor.encoderA_pin, left_motor.encoderB_pin);

void init() {
    pinMode(left_motor.dir_pin, OUTPUT);
    pinMode(left_motor.pwmh_pin, OUTPUT);
    pinMode(right_motor.dir_pin, OUTPUT);
    pinMode(right_motor.pwmh_pin, OUTPUT);
    analogWriteFrequency(left_motor.pwmh_pin, 0);
    analogWriteFrequency(right_motor.pwmh_pin, 0);
    crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1);
    if (!crsfSerial) {
        while (1) {
            Serial.println("Invalid crsfSerial configuration");
        }
    }
    crsf.begin(crsfSerial);
    rtcomSocket.begin();
    rtcomSocket.onConnection(onConnection);
}

void main() {
    executed_ch();
    open_loop_pwm(channels[0], right_motor);
    open_loop_pwm(channels[1], left_motor);
    curent_timer = micros();
    delta_t = (curent_timer - global_time) / 1000000.0f;

    get_velocity_prediction(right_motor, Enc_right, delta_t);
    get_velocity_prediction(left_motor, Enc_left, delta_t);

    Serial.println(delta_t);

    global_time = micros();

    rtcomSocket.process();
    if (rtcomSocket.isSessionConnected(socketSession)) {
        Serial.print("sending the data here");
    };

    delay(10);
}

void open_loop_pwm(uint16_t axis_data, Motor_Data &motor) {
    axis_data = constrain(axis_data, 1000, 2000);
    if (axis_data >= 1450 && axis_data <= 1550) {  // Neutral position
        motor.pwm_value = 0;
    } else if (axis_data > 1550) {  // Forward
        motor.pwm_value = map(axis_data, 1550, 2000, 0, 255);
        motor.direction = 1;
    } else if (axis_data < 1450) {  // Backward
        motor.pwm_value = map(axis_data, 1000, 1450, 255, 0);
        motor.direction = 0;
    }
    digitalWrite(motor.dir_pin, motor.direction);
    analogWrite(motor.pwmh_pin, motor.pwm_value);
}

void get_velocity_prediction(Motor_Data &motor, Encoder &encoder, double dt) {
    motor.encoder_read = encoder.read();
    double revolutions = static_cast<double>(motor.encoder_read) / PPR;
    double omega = (revolutions * 2.0 * M_PI) / dt;
    motor.xk = motor.xk_1 + (motor.vk_1 * dt);
    motor.vk = motor.vk_1;
    motor.rk = motor.encoder_read - motor.xk;
    motor.xk += motor.a * motor.rk;
    motor.vk += (motor.b * motor.rk) / dt;
    motor.xk_1 = motor.xk;
    motor.vk_1 = omega;  // Use computed angular velocity
    motor.wheel_linera_speed = motor.vk_1 * RADIOUS_MM;
}

int motor_pid(Motor_Data &motor, Encoder &encoder, double dt, uint16_t axis_data) {
    get_velocity_prediction(motor, encoder, dt);
}

void emit_data() {
}

void executed_ch() {
    crsf.update();
    for (size_t i = 0; i < NUM_CHANNELS; i++) {
        channels[i] = crsf.getChannel(i + 1);
    }
}

void onConnection(RTComSession &session) {
    Serial.printf("Session created with %s\r\n", session.address.toString());
    socketSession = &session;
    Serial.print("connect");

    session.onReceive([](const uint8_t *bytes, size_t size) {
        char data[size + 1] = {0};
        memcpy(data, bytes, size);
        Serial.println(data);
    });
}

}  // namespace G_BOT
