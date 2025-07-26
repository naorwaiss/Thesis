#include "swing_drone/micros_lib.hpp"
#include <chrono>

// Implementation of micros() function for Arduino-like timing
unsigned long micros() {
    static auto start_time = std::chrono::high_resolution_clock::now();
    auto current_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);
    return static_cast<unsigned long>(duration.count());
} 