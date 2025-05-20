#include "src/gnd_class.h"
#include "src/RTCom/RTCom.h"
#include "src/sender.h"
#include "src/roller.h"
#include <AlfredoCRSF.h>
#include "src/ImuMadgwick.h"
#include "Wire.h"

#define crsfSerial Serial1  // Use Serial1 for the CRSF communication
#define NUM_CHANNELS 16

#define right_motor_pwmh_pin 3 // for the ground bot
#define right_motor_dir_pin 2   // for the ground bot
#define left_motor_pwmh_pin 5 // for the ground bot
#define left_motor_dir_pin 4   // for the ground bot
#define right_motor_encoderA_pin 7 // for the ground bot
#define right_motor_encoderB_pin 6 // for the ground bot
#define left_motor_encoderA_pin 8 // for the ground bot
#define left_motor_encoderB_pin 9 // for the ground bot


//have problem with this pin
#define roller_motor_INA_pin 36
#define roller_motor_INB_pin 33
#define roller_motor_PWM_pin 15
#define roller_motor_ENA_pin 37
#define DOUT_data 14
#define CLK_data 13

#define loop_time_hz 200
elapsedMicros loop_time;
const double dt_loop = 1000000.0 / loop_time_hz;
double time_sec = 1.0/loop_time_hz;
uint16_t channels[NUM_CHANNELS];  // RC channel values

constexpr uint8_t IP_ADDRESS[4] = {192, 168, 1, 177};
constexpr uint16_t PORT_NUMBER = 8888;
const SocketAddress SOCKET_ADDRESS = SocketAddress(IP_ADDRESS, PORT_NUMBER);
RTCom rtcomSocket(SOCKET_ADDRESS, RTComConfig(1, 100, 200, 500));
RTComSession *socketSession = nullptr;
AlfredoCRSF crsf;
gnd_bot gnd_platform(time_sec,right_motor_pwmh_pin, right_motor_dir_pin, left_motor_pwmh_pin, left_motor_dir_pin, right_motor_encoderA_pin, right_motor_encoderB_pin, left_motor_encoderA_pin, left_motor_encoderB_pin);
roller roller_instance(time_sec, roller_motor_ENA_pin, roller_motor_INA_pin , roller_motor_INB_pin, roller_motor_PWM_pin, DOUT_data, CLK_data);
ImuMadgwick imu(&Wire1,loop_time_hz);
sender sender_instance(socketSession, &gnd_platform, &roller_instance);

void onConnect(RTComSession &session) {
    socketSession = &session;
    Serial.print("Created session with ");
    sender_instance.update_session(session);
    Serial.println(socketSession->address.toString());
}
void executed_ch() {
    crsf.update();
    for (size_t i = 0; i < NUM_CHANNELS; i++) {
        channels[i] = crsf.getChannel(i + 1);
    }
}

void setup() {
    Serial.begin(115200);
    // crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1);
    gnd_platform.init();
    roller_instance.init_roller();
    roller_instance.set_pid_param(10, 0.0, 0.0);
    // rtcomSocket.begin();
    // rtcomSocket.onConnection(onConnect);
}

void loop() {
    // executed_ch();
    if (loop_time > dt_loop) {
        rtcomSocket.process();
        // float omega_dot_cmmand = constrain(map(channels[0], 1000, 2000, -1, 1), -1, 1);
        // float x_dot_cmmand = constrain(map(channels[2], 1000, 2000, -1, 1), -1, 1);
        // gnd_platform.main(omega_dot_cmmand, x_dot_cmmand);
        roller_instance.main_roller();
        loop_time = 0;
    }
}