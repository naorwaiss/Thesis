

///////////////////////////////////////////////////////////////////////////

#include <AlfredoCRSF.h>
#include <Arduino.h>
#include <Wire.h>

// Pin and motor values
// #define MOTOR1_PIN 5

#define PWM_RESOLUTION 12  // 12-bit resolution
#define ESC_FREQUENCY 400  // 250Hz
#define PWM_PERIOD 1000000 / ESC_FREQUENCY
#define PWM_MAX ((1 << PWM_RESOLUTION) - 1)  // 4095 for 12-bit
#define PWM_MIN (1000 * PWM_MAX) / (1000000 / ESC_FREQUENCY)
#define US_2_PULSE(u) ((u) * PWM_MAX / (PWM_PERIOD))
// #define US_3_PULSE(u) ((u)* 2.048*1.2)
#define MAX 4095.00

// #define pwm(u) ((u)* PWM_MAX / (pow(2,)))

#define motor_1 2
#define motor_2 3
#define motor_3 4
#define motor_4 5

int motor_list[] = {motor_1, motor_2, motor_3, motor_4};

// Instantiate AlfredoCRSF object
AlfredoCRSF crsf;
uint16_t channels[16];  // RC channel values
int PWM = 0;
float PWM_val = 0;

void setup() {
    Serial.begin(115200);  // USB Serial for debugging
    // while (!Serial); // Wait for the Serial Monitor to open
    // Serial.println("USB Serial initialized");

    // Initialize Serial1 for CRSF communication
    Serial1.begin(420000);  // Use default pins for Serial1
    if (!Serial1) {
        Serial.println("Failed to initialize Serial1");
        while (1);  // Halt if Serial1 fails
    }
    delay(1000);

    // Initialize CRSF with Serial1
    crsf.begin(Serial1);
    Serial.println("CRSF initialized");

    if (!Serial1) {
        while (1) {
            Serial.println("Invalid crsfSerial configuration");
        }
    }

    crsf.update();
    printChannels();
    delay(1000);

    for (size_t i = 0; i < 4; i++) {
        pinMode(motor_list[i], OUTPUT);
        analogWriteFrequency(motor_list[i], ESC_FREQUENCY);
        analogWriteResolution(12);
    }
}

void loop() {
    // Update CRSF data
    crsf.update();  // Call update to process CRSF data

    // Print channel data as fast as possible
    printChannels();

    int map_pwm = map(channels[2], 988, 2012, 1000, 2000);

    PWM_val = US_2_PULSE(map_pwm);

    // PWM_val = PWM_val +500;

    // if (map_pwm<0)
    // {
    //     map_pwm = 0;
    // }

    // analogWrite(motor_list[2], PWM_val);
// 
    for (size_t i = 0; i < 4; i++) {
        analogWrite(motor_list[i], PWM_val);
        /* code */
    }
    // analogWrite(motor_list[0], PWM_val);



    // Serial.print("the enter of the data of the rc ");
    // Serial.println(channels[2]);

    Serial.print("Channel Values after amit : ");
    Serial.println(PWM_val);

    // }

    // analogWrite(MOTOR1_PIN, map(channels[2],1100,1900,1300,1864));
    // Serial.println(channels[2]);
    delay(10);
}

// Function to print all 16 CRSF channel values
void printChannels() {
    for (int channelNum = 1; channelNum <= 16; channelNum++) {
        channels[channelNum - 1] = crsf.getChannel(channelNum);
        // Serial.print(channels[channelNum-1]);
        // Serial.print(", ");
    }
    // Serial.println();
}
