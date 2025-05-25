#define roller_motor_INA_pin 25
#define roller_motor_INB_pin 33
#define roller_motor_PWM_pin 15
#define roller_motor_ENA_pin 11

void setup() {
  // Set motor control pins as outputs
  pinMode(roller_motor_INA_pin, OUTPUT);
  pinMode(roller_motor_INB_pin, OUTPUT);
  pinMode(roller_motor_PWM_pin, OUTPUT);
  pinMode(roller_motor_ENA_pin, OUTPUT);

  // Enable motor
  digitalWrite(roller_motor_ENA_pin, HIGH);
}

void loop() {
  // Rotate motor forward
  digitalWrite(roller_motor_INA_pin, HIGH);
  digitalWrite(roller_motor_INB_pin, LOW);
  analogWrite(roller_motor_PWM_pin, 128);  // Half speed (0–255)
    Serial.println("Motor running forward");
  delay(2000);  // Run for 2 seconds

  // Stop motor
  analogWrite(roller_motor_PWM_pin, 0);
    Serial.println("Motor stopped");
  delay(1000);

  // Rotate motor backward
  digitalWrite(roller_motor_INA_pin, LOW);
  digitalWrite(roller_motor_INB_pin, HIGH);
  analogWrite(roller_motor_PWM_pin, 200);  // Faster speed

  delay(2000);  // Run for 2 seconds

  // Stop motor again
  analogWrite(roller_motor_PWM_pin, 0);
    Serial.println("Motor stopped");
  delay(1000);

}
