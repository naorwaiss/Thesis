#include <Dynamixel2Arduino.h>
#include <AlfredoCRSF.h>
#include "src/Diff_Robot.h"
// AlfredoCRSF crsf;
#define DXL_SERIAL Serial1
#define DEBUG_SERIAL Serial
#define CRSF_SERIAL Serial5
#define DXL_DIR_PIN 2
#define REAR_RIGHT_1 1
#define REAR_RIGHT_2 2
#define REAR_LEFT_1 3
#define REAR_LEFT_2 4
#define FRONT_RIGHT 5
#define FRONT_LEFT 6

Diff_Robot diff_robot(REAR_RIGHT_1, REAR_RIGHT_2, REAR_LEFT_1, REAR_LEFT_2, FRONT_RIGHT, FRONT_LEFT, DXL_DIR_PIN, DXL_SERIAL);

// This namespace is required to use Control table item names
using namespace ControlTableItem;


void setup() {
}

void loop() {
}