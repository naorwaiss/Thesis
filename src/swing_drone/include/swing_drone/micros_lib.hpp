#ifndef MICROS_LIB_HPP_
#define MICROS_LIB_HPP_

#include <chrono>

// Forward declaration of micros function (implemented in flight_controller_main.cpp)
unsigned long micros();

/**
 * elapsed_timer - A utility class for precise loop timing control in ROS2 environment
 * 
 * This class helps maintain consistent loop execution timing by tracking
 * elapsed time and determining when the next iteration should occur.
 * Compatible with the existing Arduino-like structure in flight_controller_main.cpp
 * 
 * Usage Example:
 *   elapsed_timer loop_timer(50.0f);  // 50 Hz (20ms intervals)
 *   
 *   void loop() {
 *     if (loop_timer.has_elapsed()) {
 *       // Your main loop code here
 *       // This will execute at approximately 50 Hz
 *       
 *       loop_timer.reset();  // Reset for next iteration
 *     }
 *   }
 */
class elapsed_timer {
public:
    /**
     * Constructor
     * @param dt_hz Desired frequency in Hz (loops per second)
     */
    elapsed_timer(float dt_hz) : _dt_hz(dt_hz) {
        _dt_micros = static_cast<unsigned long>(1000000.0f / _dt_hz);
        reset();
    }

    /**
     * Reset the timer to current time
     * Call this after each successful loop iteration
     */
    void reset() {
        _loop_time = micros();
    }

    /**
     * Check if enough time has elapsed for next iteration
     * @return true if it's time for the next loop iteration
     */
    bool has_elapsed() {
        return (micros() - _loop_time) >= _dt_micros;
    }

    /**
     * Get the actual elapsed time in microseconds
     * @return microseconds since last reset
     */
    unsigned long get_elapsed_micros() {
        return micros() - _loop_time;
    }

    /**
     * Get the actual elapsed time in milliseconds
     * @return milliseconds since last reset
     */
    float get_elapsed_millis() {
        return static_cast<float>(micros() - _loop_time) / 1000.0f;
    }

    /**
     * Get the target loop frequency
     * @return frequency in Hz
     */
    float get_frequency() {
        return _dt_hz;
    }

    /**
     * Get the target loop period
     * @return period in microseconds
     */
    unsigned long get_period_micros() {
        return _dt_micros;
    }

    /**
     * Check if we're running behind schedule
     * @return true if current loop is taking longer than target period
     */
    bool is_overrun() {
        return get_elapsed_micros() > _dt_micros;
    }

    /**
     * Get timing statistics for debugging
     * @return timing ratio (actual_time / target_time)
     */
    float get_timing_ratio() {
        return static_cast<float>(get_elapsed_micros()) / static_cast<float>(_dt_micros);
    }

private:
    float _dt_hz;                    // Target frequency in Hz
    unsigned long _dt_micros;        // Target period in microseconds
    unsigned long _loop_time;        // Last reset time in microseconds
};

#endif // MICROS_LIB_HPP_ 