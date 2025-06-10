// === PIN SETUP===
const int POT_YAW_PIN = A0;       //Yaw angle(Yaw)
const int POT_PITCH_PIN = A1;     // pitch angle(Pitch)
const int ENCODER_A_PIN = 2;      // ערוץ A של אינקודר
const int ENCODER_B_PIN = 3;      // ערוץ B של אינקודר

// === ENCODER SETUP===
const float ROOLER_RADIUS_M = 0.0305;      // לבדוק מה הרדיוס
const float PPR = 1425.1;              // Pulses Per Revolution 

// ===POTIENTIOMETER SETUP
const int POT_MIN = 0;
const int POT_MAX = 1023;
const float YAW_MIN_DEG = 0.0;           // לבדוק איזה זווית מתאימה למה ולהכניס את הערכים
const float YAW_MAX_DEG = 180.0;
const float PITCH_MIN_DEG = 0.0;
const float PITCH_MAX_DEG = 90.0;

// === משתנים ===
volatile long encoderCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENCODER_A_PIN, INPUT);
  pinMode(ENCODER_B_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), handleEncoder, RISING);
}

void loop() {
  int rawYaw = analogRead(POT_YAW_PIN);
  int rawPitch = analogRead(POT_PITCH_PIN);
  float yawDeg = mapFloat(rawYaw, POT_MIN, POT_MAX, YAW_MIN_DEG, YAW_MAX_DEG);
  float pitchDeg = mapFloat(rawPitch, POT_MIN, POT_MAX, PITCH_MIN_DEG, PITCH_MAX_DEG);

  //L(t)
  float thetaDeg = ((float)encoderCount / PPR) * 360.0;
  float length_m = 2 * PI *ROOLER_RADIUS_M * (thetaDeg / 360.0);

  // radian change
  float yawRad = radians(yawDeg);
  float pitchRad = radians(pitchDeg);

  // 3D LOCATION
  float x = length_m * cos(pitchRad) * sin(yawRad);
  float y = length_m * sin(pitchRad);
  float z = length_m * cos(pitchRad) * cos(yawRad);
  Serial.print("Yaw: "); Serial.print(yawDeg);
  Serial.print("°, Pitch: "); Serial.print(pitchDeg);
  Serial.print("°, Length: "); Serial.print(length_m, 3); Serial.print(" m");
  Serial.print(" | Position (x,y,z) [m]: ");
  Serial.print(x, 3); Serial.print(", ");
  Serial.print(y, 3); Serial.print(", ");
  Serial.println(z, 3);

  delay(200);
}

void handleEncoder() {
  int b = digitalRead(ENCODER_B_PIN);
  encoderCount += (b == HIGH) ? 1 : -1;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
