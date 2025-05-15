#include "src/gnd_class.h"

#define right_motor_pwmh_pin 3
#define right_motor_dir_pin 2
#define left_motor_pwmh_pin 5
#define left_motor_dir_pin 4
#define right_motor_encoderA_pin 7
#define right_motor_encoderB_pin 6
#define left_motor_encoderA_pin 8
#define left_motor_encoderB_pin 9

#define loop_time_hz 200
elapsedMicros loop_time;
const double dt_loop = 1000000.0 / loop_time_hz;
double time_sec = 1/loop_time_hz;

gnd_bot gnd_platform(time_sec,right_motor_pwmh_pin, right_motor_dir_pin, left_motor_pwmh_pin, left_motor_dir_pin, right_motor_encoderA_pin, right_motor_encoderB_pin, left_motor_encoderA_pin, left_motor_encoderB_pin);

void setup() {
    gnd_platform.init();

}

void loop() {
    if (loop_time > dt_loop) {
        // gnd_platform.main();
        loop_time = 0;
    }

}