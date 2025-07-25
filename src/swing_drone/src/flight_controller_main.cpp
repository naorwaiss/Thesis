#include <iostream>
#include <chrono>
#include <thread>

// Global variables
bool system_initialized = false;
int counter = 0;
const int LOOP_FREQUENCY_HZ = 50; // Set desired loop frequency here
const auto LOOP_PERIOD_MICROS = std::chrono::microseconds(1000000 / LOOP_FREQUENCY_HZ);

// Function similar to Arduino's micros()
unsigned long micros() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

// Arduino-like init function
void init() {
    std::cout << "Flight Controller Initializing..." << std::endl;
    
    // Initialize your flight controller here
    counter = 0;
    system_initialized = true;
    
    std::cout << "Flight Controller Initialized!" << std::endl;
    std::cout << "Running at " << LOOP_FREQUENCY_HZ << " Hz" << std::endl;
}

// Arduino-like loop function
void loop() {
    if (!system_initialized) return;
    
    static auto last_loop_time = std::chrono::high_resolution_clock::now();
    
    // Main flight controller logic here
    counter++;
    
    std::cout << "Flight Controller Loop #" << counter << " at " << micros() << " microseconds" << std::endl;
    
    // Add your flight control logic here
    // This runs continuously like Arduino loop()
    
    // Precise timing control - maintain specific Hz
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed = current_time - last_loop_time;
    
    if (elapsed < LOOP_PERIOD_MICROS) {
        std::this_thread::sleep_for(LOOP_PERIOD_MICROS - elapsed);
    }
    
    last_loop_time = std::chrono::high_resolution_clock::now();
}

int main() {
    // Call init once
    init();
    
    // Run loop continuously
    while (true) {
        loop();
    }
    
    return 0;
}
