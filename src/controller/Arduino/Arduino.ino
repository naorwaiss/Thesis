#include <Arduino.h>
#include "src/Drone_com.h"
#include <AlfredoCRSF.h>

#define crsfSerial Serial2  // Use Serial1 for the CRSF communication
#define NUM_CHANNELS 14

uint16_t channels[NUM_CHANNELS];  // RC channel values

void setup() {
    ELRS_REMOTE::init_com();
}

void loop() {
    // executed_ch();
    ELRS_REMOTE::main_loop();
    delay(1);
    
}

