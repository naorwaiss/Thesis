#include <Arduino.h>
#include "src/Drone_com.h"
#include <AlfredoCRSF.h>

#define crsfSerial Serial2  // Use Serial1 for the CRSF communication
#define NUM_CHANNELS 14

AlfredoCRSF crsf;
uint16_t channels[NUM_CHANNELS];  // RC channel values

void setup() {
    ELRS_REMOTE::init_com();
    crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1);
}

void loop() {
    executed_ch();
    
}


void executed_ch() {
    crsf.update();
    for (size_t i = 0; i < NUM_CHANNELS; i++) {
        channels[i] = crsf.getChannel(i + 1);
    }
}