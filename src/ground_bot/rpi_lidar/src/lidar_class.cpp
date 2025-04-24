#include "lidar_class.h"

lidar_class::lidar_class(lidar_class_data* data, RTComSession* Session) {
    // Constructor implementation
    // Initialize the lidar_class with the provided data structure
    measurement = data;
    socketSession = Session;
}

void lidar_class::updateSession(RTComSession* newSession) {
    socketSession = newSession;
}

void lidar_class::init_lidar() {
    
}
