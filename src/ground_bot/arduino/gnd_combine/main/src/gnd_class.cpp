#include "gnd_class.h"

gnd_bot::gnd_bot(double dt_loop, uint8_t pwmh_right, uint8_t dir_right, uint8_t pwmh_left, uint8_t dir_left,
                 uint8_t encoderA_right, uint8_t encoderB_right, uint8_t encoderA_left, uint8_t encoderB_left)
    : right_encoder(encoderA_right, encoderB_right),
      left_encoder(encoderA_left, encoderB_left) {
    right_motor.pwmh_pin = pwmh_right;
    right_motor.dir_pin = dir_right;
    right_motor.encoderA_pin = encoderA_right;
    right_motor.encoderB_pin = encoderB_right;
    right_motor.direction = false;
    left_motor.pwmh_pin = pwmh_left;
    left_motor.dir_pin = dir_left;
    left_motor.encoderA_pin = encoderA_left;
    left_motor.encoderB_pin = encoderB_left;
    left_motor.direction = false;
    this->dt_sec = dt_loop;
}

void gnd_bot::set_alfa_beta(float alfa = 0.85, float beta = 0.005) {
    right_motor.a = alfa;
    right_motor.b = beta;
    left_motor.a = alfa;
    left_motor.b = beta;
}

void gnd_bot::set_pid_param(float Kp = 2, float Ki = 0.5, float Kd = 0.1) {
    right_motor.Kp = Kp;
    right_motor.Ki = Ki;
    right_motor.Kd = Kd;
    left_motor.Kp = Kp;
    left_motor.Ki = Ki;
    left_motor.Kd = Kd;
}

void gnd_bot::get_velocity_prediction(Motor_Data &motor, Encoder &encoder) {
    /// i think have here some problem with the filter 
    motor.encoder_read = encoder.read();
    Serial.println(motor.encoder_read);
    double revolutions = static_cast<double>(motor.encoder_read) / PPR;
    double omega = (revolutions * 2.0 * M_PI) / this->dt_sec;
    motor.xk = motor.xk_1 + (motor.vk_1 * this->dt_sec);
    motor.vk = motor.vk_1;
    motor.rk = motor.encoder_read - motor.xk;
    motor.xk += motor.a * motor.rk;
    motor.vk += (motor.b * motor.rk) / this->dt_sec;
    motor.xk_1 = motor.xk;
    motor.vk_1 = omega;  // Use computed angular velocity
    motor.omega_drive_wheel = omega; 
    motor.wheel_linera_speed = motor.vk_1 * (RADIOUS_MM / 1000);
}



void gnd_bot::init() {
    pinMode(left_motor.dir_pin, OUTPUT);
    pinMode(left_motor.pwmh_pin, OUTPUT);
    pinMode(right_motor.dir_pin, OUTPUT);
    pinMode(right_motor.pwmh_pin, OUTPUT);
    analogWriteFrequency(left_motor.pwmh_pin, 0);
    analogWriteFrequency(right_motor.pwmh_pin, 0);
    set_alfa_beta();
    set_pid_param();
}

void gnd_bot::open_loop_pwm(uint16_t axis_data, Motor_Data &motor) {
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

void gnd_bot::get_twist_msg() {
    robot.x_dot_estimate = (left_motor.wheel_linera_speed + right_motor.wheel_linera_speed) / 2;
    robot.omega_dot_estimate = (right_motor.wheel_linera_speed - left_motor.wheel_linera_speed) / (DISTANCE_BETWEEN_WHEELS / 1000);
}

void gnd_bot::position_estimate() {
    get_twist_msg();
    double delta_theta = robot.omega_dot_estimate * this->dt_sec;
    double theta_mid = robot.omega_estimate + delta_theta / 2.0;

    double delta_x = robot.x_dot_estimate * this->dt_sec * cos(theta_mid);
    double delta_y = robot.x_dot_estimate * this->dt_sec * sin(theta_mid);

    robot.x_estimate += delta_x;
    robot.y_estimate += delta_y;
    robot.omega_estimate += delta_theta;
    robot.omega_estimate = atan2(sin(robot.omega_estimate), cos(robot.omega_estimate));
}

int gnd_bot::motor_pid_omega(Motor_Data &motor, Encoder &encoder, double dt, uint16_t axis_data) {
    int pwm_out = 0;
    float goal = 0.0, error = 0.0, derivative = 0.0;
    goal = map(axis_data, 1000, 2000, 0, max_omga);  /// need to fix it with the direction
    // get_velocity_prediction(motor, encoder, dt);
    error = goal - motor.omega_drive_wheel;
    motor.integral += error * dt;
    derivative = (error - motor.prev_error) / dt;  // Compute derivative
    motor.pid_out = (motor.Kp * error) + (motor.Ki * motor.integral) + (motor.Kd + derivative);
    motor.prev_error = error;
}

void gnd_bot::main(float omega_dot, float x_dot) {
    open_loop_pwm(1000, right_motor);
    get_velocity_prediction(right_motor, right_encoder);
    // get_velocity_prediction(left_motor, left_encoder);
    // robot.omega_dot_cmmand = omega_dot;
    // robot.x_dot_cmmand = x_dot;
    // get_twist_msg();
}