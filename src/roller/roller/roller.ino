#include <Encoder.h>

// Define pin assignments
const int INA_PIN = 2;
const int INB_PIN = 3;
const int PWM_PIN = 4;


const int VRxPin = 14; // X-axis analog input (Pin A0 on most Arduinos)


// Encoder pins
const int ENCODER_A_PIN = 6; // Encoder A
const int ENCODER_B_PIN = 7; // Encoder B



/// globals
int xValue = 0;
float pwm_value = 0.0;
unsigned long previousTime = 0;
long position = 0;
long prev_position = 0;
float angular_velocity = 0;
const float counts_per_rev = 	1425.1;   // GoBilda motor's encoder PPR



// Create an Encoder object
Encoder motorEncoder(ENCODER_A_PIN, ENCODER_B_PIN);

void setup() {
  // Set pin modes for motor control
  pinMode(INA_PIN, OUTPUT);
  pinMode(INB_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  // Initialize motor stopped
  digitalWrite(INA_PIN, LOW);
  digitalWrite(INB_PIN, LOW);
  analogWrite(PWM_PIN, 0);


  // Start serial communication
  Serial.begin(115200);
  Serial.println("Motor control with encoder ready!");
  previousTime = micros();

}

void loop() {
  /// dt time calculation
  unsigned long currentTime = micros();
  unsigned long dt = currentTime - previousTime;
  previousTime = currentTime;

  xValue = analogRead(VRxPin);

  direct_pwm(); //// direct pwm to the motor via the joystick
  encoder_to_velo(dt);



  delay(100);

}










void direct_pwm(){
  /// the direct pwm to via the joystick

if (xValue > 800) {
    pwm_value = map(xValue, 800, 1023, 0, 255);
    //.rotate left 
    digitalWrite(INA_PIN, HIGH);
    digitalWrite(INB_PIN, LOW);
    analogWrite(PWM_PIN, pwm_value);
} 
else if (xValue < 700) { // Explicit range
    pwm_value = map(xValue, 700, 0, 0, 255);
    digitalWrite(INA_PIN, LOW); // Reverse direction
    digitalWrite(INB_PIN, HIGH);
    analogWrite(PWM_PIN, pwm_value);
}
 else {
    pwm_value = 0;
    analogWrite(PWM_PIN, pwm_value);
    digitalWrite(INA_PIN, LOW);
    digitalWrite(INB_PIN, LOW); // Stop motor
}



    // Get and print encoder count
  position = motorEncoder.read();
  Serial.print("Encoder Count: ");
  Serial.println(position);






}










void encoder_to_velo(unsigned long dt) {


  if (dt == 0) {
    Serial.println("Error: dt is zero");
    return;
  }

  long position = motorEncoder.read();
 
  float delta_counts = static_cast<float>(position - prev_position);

  // If no displacement, angular velocity is zero
  if (delta_counts == 0) {
    Serial.print("Encoder Count: ");
    Serial.println(position);
    Serial.println("Angular Velocity (radians/sec): 0.00");
    return;
  }

  // Calculate angular displacement (in radians)
  float delta_theta = 2.0 * PI * (delta_counts / counts_per_rev);

  // Convert dt to seconds (dt is in microseconds)
  float dt_seconds = static_cast<float>(dt) / 1e6;

  // Calculate angular velocity (radians per second)
  angular_velocity = delta_theta / dt_seconds;

  // Debug print for dt and displacement
  Serial.print("Delta Counts: ");
  Serial.println(delta_counts);
  Serial.print("Delta Time (s): ");
  Serial.println(dt_seconds, 6);

  // Print results
  Serial.print("Encoder Count: ");
  Serial.println(position);
  Serial.print("Angular Velocity (radians/sec): ");
  Serial.println(angular_velocity, 2);

  // Update previous position for next calculation
  prev_position = position;
}






void velocity_control(){
  /// need to add 




}



void current_read(){
  // need to add 




}