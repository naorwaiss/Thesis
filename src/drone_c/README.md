# Drone Control System (drone_c) - Comprehensive Documentation

A complete drone control system featuring real-time communication, advanced control algorithms, and automated performance analysis. This system integrates Arduino-based flight control with ROS 2 for comprehensive drone management and analysis.

## 🚁 System Overview

The drone_c library is a comprehensive drone control system that combines:
- **Arduino-based flight controller** with real-time sensor processing
- **RTCom communication protocol** for low-latency data transmission
- **ROS 2 integration** for high-level control and analysis
- **Advanced control algorithms** including PID, EKF, and Madgwick filtering -> at this stage the compclass is the acurate 
- **Automated performance analysis** with second-order system fitting -> TBD
- **Reinforcement learning capabilities** for adaptive control - > TBD

## 🏗️ System Architecture

### Hardware Components
- **Flight Controller**: Arduino-compatible board (Teensy recommended)
- **Sensors**: LSM6DSO (IMU), LIS3MDL (Magnetometer), LPS (Barometer)
- **Motors**: 4x brushless motors with ESC control
- **Receiver**: ELRS (ExpressLRS) for radio control
- **Communication**: WiFi/Ethernet for RTCom data transmission

### Software Components
- **Arduino Firmware**: Real-time flight control and sensor processing
- **RTCom Library**: Custom communication protocol for low-latency data transfer
- **ROS 2 Nodes**: Data processing, analysis, and high-level control
- **Control Algorithms**: PID, EKF, Madgwick, and complementary filters
- **Analysis Tools**: Automated performance evaluation and system identification

## 🔧 Arduino Flight Controller

### Core Features
The Arduino firmware provides real-time flight control with the following capabilities:

#### Sensor Processing
- **IMU Data**: Accelerometer and gyroscope readings with bias calibration
- **Magnetometer**: Compass data for heading estimation
- **Barometer**: Altitude and pressure measurements
- **Filtering**: Multiple filtering options (Complementary, Madgwick, EKF)

#### Control Modes
1. **Rate Mode** (`MODE_RATE`): Direct angular rate control
   - Maps controller inputs directly to desired angular rates
   - Provides maximum maneuverability for experienced pilots
   - Uses rate PID controllers for stabilization

2. **Stabilize Mode** (`MODE_STABILIZE`): Angle-based control
   - Maps controller inputs to desired attitude angles
   - Automatically maintains level flight
   - Uses cascaded PID control (attitude → rate → motor)

3. **Loitering Mode (`LOITER`): ->TBD

#### Flight Control Loop
```cpp
// Main control loop running at 1kHz
void loop() {
    update_controller();           // Read RC inputs
    check_arming_state();          // Safety checks
    
    if (imu_timer >= IMU_PERIOD) {
        Update_Measurement();      // Read sensors
        std_filter.all_filter();   // Apply filters
        
        if (drone_data_header.is_armed) {
            if (controller_data.aux1 > 1500) {
                // Stabilize mode
                PID_stab_out = PID_stab(desired_attitude, estimated_attitude, estimated_rate, t_PID_s);
                desired_rate = PID_stab_out.PID_ret;
            } else {
                // Rate mode
                mapping_controller();
            }
            
            // Rate control
            PID_rate_out = PID_rate(desired_rate, estimated_rate, t_PID_r);
            motors.Motor_Mix(PID_rate_out.PID_ret, controller_data.throttle);
        }
    }
}
```

#### Filtering Options
The system supports three attitude estimation methods:

1. **Complementary Filter** (`COMPCLASS`) - > this is a magwick with dynamic beta 
   - Fast and computationally efficient
   - Combines gyroscope and accelerometer data
   - Good for basic stabilization

2. **Madgwick Filter** (`MADGWICK`)
   - Advanced quaternion-based algorithm
   - Excellent performance with magnetometer
   - Adaptive gain based on motion

3. **Extended Kalman Filter** (`KALMAN`)
   - Most sophisticated estimation method
   - Handles sensor noise optimally
   - Computationally intensive but highly accurate

### Key Arduino Files

#### `Arduino.ino` - Main Flight Controller
- **Initialization**: Sensor setup, calibration, and system configuration
- **Main Loop**: Real-time control execution at 1kHz
- **Safety**: Arming/disarming logic and failsafe mechanisms
- **Mode Switching**: Rate vs Stabilize mode selection

#### `src/Var_types.h` - Data Structures
```cpp
// Core data structures for the system
typedef struct {
    vec3_t acc, gyroRAD, gyroDEG, mag;
    vec3_t acc_LPF, gyro_HPF, gyro_LPF, mag_LPF;
    vec3_t acc_bias, gyro_bias, mag_bias;
    baro_t baro_data;
} Measurement_t;

typedef struct {
    float roll, pitch, yaw;
} attitude_t;

typedef struct {
    attitude_t error, P_term, I_term, D_term, PID_ret;
    attitude_t prev_err, prev_Iterm, prev_Dterm;
} PID_out_t;
```

#### `src/PID_type.cpp` - PID Control Implementation
- **Rate PID**: Controls angular rates (roll, pitch, yaw)
- **Stabilize PID**: Controls attitude angles
- **Anti-windup**: Prevents integral term saturation
- **Filtering**: High-pass filters for derivative terms

#### `src/MotorsControl.cpp` - Motor Management
- **Motor Mixing**: Converts PID outputs to motor commands
- **PWM Control**: Direct ESC control via PWM signals
- **Safety**: Motor arming/disarming and failsafe

## 📡 RTCom Communication Protocol

### Overview
RTCom (Real-Time Communication) is a custom UDP-based protocol designed for low-latency, reliable data transmission between the Arduino flight controller and ROS 2 system.

### Protocol Features
- **Typed Messages**: Each message type has a unique identifier
- **Connection Management**: Automatic connection establishment and monitoring
- **Reliability**: Ping/pong mechanism for connection health monitoring
- **Low Latency**: Optimized for real-time control applications

### Message Types
```cpp
#define MAG 'a'                    // Magnetometer data
#define P_IMU_RAW 'b'              // Raw IMU data
#define P_IMU_FILTER 'c'           // Filtered IMU data
#define EUILER 'd'                 // Euler angles
#define RC 'e'                     // Radio control inputs
#define Quaternion_n 'f'           // Quaternion orientation
#define D_RATE 'g'                 // Desired angular rates
#define D_ATI 'h'                  // Desired attitude angles
#define MOTOR_DATA_CONST 'i'       // Motor PWM values
#define EST_RATE 'j'               // Estimated angular rates
#define PID_stab_prase 'k'         // Stabilize PID data
#define PID_rate_prase 'l'         // Rate PID data
#define PID_CONSTS_DATA 'm'        // PID constants
#define DRONE_SIGNATURE 'n'        // Drone status and mode
#define PID_CONSTS_RETURN 'z'      // PID constants feedback
```

### Communication Flow
1. **Arduino Side** (`src/drone_comclass.cpp`):
   - Collects sensor and control data
   - Converts to byte arrays
   - Sends via RTCom protocol

2. **ROS 2 Side** (`src/rtcom_teensy_ros.py`):
   - Receives RTCom messages
   - Converts to ROS 2 messages
   - Publishes to appropriate topics

### Network Configuration
```cpp
// Arduino configuration
uint8_t SOCKET_IP_ADDRESS[4] = {192, 168, 1, 199};
uint16_t SOCKET_PORT_NUMBER = 8888;
RTComConfig SOCKET_CONFIG{1, 100, 200, 500};
```

## 🤖 ROS 2 Integration

### Core Nodes

#### `rtcom_teensy_ros.py` - Communication Bridge
- **RTCom Client**: Receives data from Arduino via RTCom protocol
- **ROS Publishers**: Converts data to ROS 2 messages
- **Message Handling**: Processes all message types with appropriate callbacks

**Published Topics:**
- `/imu_data` - Raw IMU sensor data
- `/euler_angles_data` - Estimated attitude angles
- `/desire_rate` - Desired angular rates
- `/desire_stab` - Desired attitude angles
- `/estimated_rate` - Estimated angular rates
- `/motor_pwm` - Motor PWM values
- `/PID_stab` - Stabilize PID controller data
- `/PID_rate` - Rate PID controller data
- `/drone_header` - Drone status and mode information

#### `control_optimize.py` - Performance Analysis
- **Real-time Analysis**: Automatically analyzes control performance
- **Data Collection**: Buffers control data for analysis
- **System Identification**: Fits second-order transfer functions
- **Performance Metrics**: Rise time, settling time, overshoot, steady-state error

### ROS 2 Messages

#### Custom Message Types
```msg
# Pid.msg - PID controller data
float32 error_pitch, error_roll, error_yaw
float32 p_pitch, p_roll, p_yaw
float32 i_pitch, i_roll, i_yaw
float32 d_pitch, d_roll, d_yaw
float32 sum_pitch, sum_roll, sum_yaw

# DroneHeader.msg - Drone status
int32[6] mac_adress
int32 drone_mode
int32 drone_filter
bool is_armed

# EulerAngles.msg - Attitude representation
float32 roll, pitch, yaw

# Motors.msg - Motor control
float32 front_right, back_right, back_left, front_left
```

## 🎯 Control Policies and Algorithms

### PID Control Implementation

#### Rate Control PID
Controls angular rates for roll, pitch, and yaw axes:
```cpp
PID_out_t PID_rate(attitude_t desired_rate, attitude_t estimated_rate, float dt) {
    // Calculate error
    attitude_t error = {
        desired_rate.roll - estimated_rate.roll,
        desired_rate.pitch - estimated_rate.pitch,
        desired_rate.yaw - estimated_rate.yaw
    };
    
    // PID terms with anti-windup and filtering
    // Returns motor commands for each axis
}
```

#### Stabilize Control PID
Controls attitude angles with cascaded control:
```cpp
PID_out_t PID_stab(attitude_t desired_attitude, attitude_t estimated_attitude, 
                   attitude_t estimated_rate, float dt) {
    // Calculate attitude error
    attitude_t error = {
        desired_attitude.roll - estimated_attitude.roll,
        desired_attitude.pitch - estimated_attitude.pitch,
        desired_attitude.yaw - estimated_attitude.yaw
    };
    
    // PID control with rate feedback
    // Returns desired rates for rate controller
}
```

### Attitude Estimation Algorithms

#### Complementary Filter (`CompClass.cpp`)
```cpp
void CompFilter::UpdateQ(Measurement_t* meas, float dt) {
    // Combine gyroscope and accelerometer data
    // Simple but effective for basic stabilization
    // Updates quaternion estimate
}
```

#### Madgwick Filter (`Madgwick.cpp`)
```cpp
void Madgwick::madgwick_operation() {
    // Advanced quaternion-based algorithm
    // Adaptive gain based on motion
    // Excellent performance with magnetometer
}
```

#### Extended Kalman Filter (`EkfClass.cpp`)
```cpp
void EKF::run_kalman(attitude_t* estimated_attitude, quat_t* q_est) {
    // Most sophisticated estimation method
    // Optimal handling of sensor noise
    // Computationally intensive but highly accurate
}
```

### Motor Mixing Algorithm
```cpp
void Motors::Motor_Mix(attitude_t PID_ret, int throttle) {
    // Convert PID outputs to motor commands
    // Apply throttle and control mixing
    // Ensure motor limits and safety
}
```

## 📊 Performance Analysis System

### Automated Analysis Features

#### Real-time Data Collection
- **Buffer Management**: Configurable collection periods (default: 5 seconds)
- **Wait Periods**: Automatic delays between collections (default: 3 seconds)
- **Mode Detection**: Automatically switches between rate and stabilize analysis

#### Control System Analysis
```python
def analyze_step_response(self, desired, actual, name):
    # Rise Time: 10% to 90% of final value
    # Settling Time: Within 5% of final value
    # Overshoot: Maximum percentage overshoot
    # Steady-State Error: Final error value
```

#### Second-Order System Fitting
```python
def fit_second_order_system(self, response_data, time_data, final_value, name):
    # Transfer Function: G(s) = K * ωn² / (s² + 2ζωn*s + ωn²)
    # Parameters: DC Gain (K), Damping Ratio (ζ), Natural Frequency (ωn)
    # System Classification: Underdamped, Critically Damped, or Overdamped
```

### Analysis Output Example
```
============================================================
CONTROL SYSTEM ANALYSIS RESULTS
============================================================

--- Rate X ---
Rise Time (10%-90%): 0.125 s
Settling Time (5%): 0.450 s
Overshoot: 15.23%
Steady-State Error: 0.0023
Step Magnitude: 45.0000

============================================================
SECOND-ORDER SYSTEM ANALYSIS
============================================================

--- Rate X ---
DC Gain (K): 1.000
Damping Ratio (ζ): 0.456
Natural Frequency (ωn): 12.34 rad/s
Natural Frequency (fn): 1.96 Hz
Damped Frequency (ωd): 11.12 rad/s
Theoretical Rise Time: 0.118 s
Theoretical Overshoot: 20.45%
Theoretical Settling Time: 0.432 s
System Type: Underdamped
============================================================
```

## 🧠 Reinforcement Learning Integration -> tbd

### TD3 Implementation (`src/RL/TD3_learn.py`)
The system includes Twin Delayed Deep Deterministic Policy Gradient (TD3) for adaptive control:

```python
# TD3 Configuration
model = TD3("MlpPolicy", env, action_noise=action_noise, verbose=1)
model.learn(total_timesteps=10000)
```

### RL Features
- **Continuous Action Spaces**: Suitable for drone control
- **Twin Critics**: Reduces overestimation bias
- **Delayed Policy Updates**: Improves training stability
- **Target Policy Smoothing**: Regularizes policy updates

### Research Integration
The system supports research in:
- **Adaptive Dynamic Programming**: RL combined with PID control
- **Online vs Offline Learning**: Real-time vs batch learning approaches
- **Policy Optimization**: TRPO, DPO, and other advanced methods

## 🔧 Installation and Setup

### Prerequisites
- **ROS 2**: Humble or later
- **Python 3.8+**: For ROS 2 and analysis tools
- **Arduino IDE**: For firmware compilation
- **Hardware**: Compatible flight controller and sensors

### Dependencies
```bash
# Python dependencies
pip install -r requirements.txt

# ROS 2 dependencies
sudo apt install ros-humble-sensor-msgs ros-humble-std-msgs
```

### Arduino Setup
1. **Install Libraries**:
   - LSM6 (IMU)
   - LIS3MDL (Magnetometer)
   - LPS (Barometer)
   - AlfredoCRSF (ELRS receiver)

2. **Configure Hardware**:
   - Connect sensors to I2C pins
   - Configure motor pins
   - Set up ELRS receiver

3. **Upload Firmware**:
   - Open `Arduino/Arduino.ino` in Arduino IDE
   - Select correct board and port
   - Upload firmware

### ROS 2 Setup
1. **Build Workspace**:
```bash
colcon build --packages-select drone_c
source install/setup.bash
```

2. **Configure Network**:
   - Set Arduino IP address in `Arduino/src/drone_comclass.h`
   - Ensure network connectivity

3. **Launch System**:
```bash
# Start communication bridge
python3 src/rtcom_teensy_ros.py

# Start analysis system
python3 src/modern_control/control_optimize.py
```

## 🎮 Usage Guide

### Basic Operation
1. **Power Up**: Connect battery and power system
2. **Calibration**: System automatically calibrates sensors on startup
3. **Arming**: Use AUX2 switch to arm/disarm the drone
4. **Mode Selection**: Use AUX1 to switch between Rate and Stabilize modes
5. **Filter Selection**: Use AUX4 to select attitude estimation method

### Control Modes
- **Rate Mode**: Direct angular rate control for experienced pilots
- **Stabilize Mode**: Angle-based control for beginners
- **Filter Modes**: Complementary, Madgwick, or EKF for attitude estimation

### Analysis Features
- **Automatic Analysis**: Runs every 10 seconds when data is available
- **Real-time Monitoring**: View control performance in real-time
- **System Identification**: Automatic transfer function fitting
- **Performance Metrics**: Comprehensive control system evaluation

## 🔍 Troubleshooting

### Common Issues
- **No Communication**: Check network configuration and IP addresses
- **Calibration Failures**: Ensure drone is stationary during startup
- **Control Issues**: Verify PID parameters and sensor calibration
- **Analysis Problems**: Check data collection and buffer settings

### Debug Tools
- **Serial Monitor**: Arduino debug output
- **ROS Topics**: Monitor data flow with `ros2 topic echo`
- **PlotJuggler**: Visualize data streams
- **Analysis Output**: Real-time performance metrics

## 📈 Performance Optimization

### Tuning Guidelines
1. **PID Tuning**: Start with conservative values and tune incrementally
2. **Filter Selection**: Choose based on computational resources and accuracy needs
3. **Network Optimization**: Minimize latency for real-time control
4. **Analysis Configuration**: Adjust buffer sizes and analysis frequency

### Best Practices
- **Safety First**: Always test in safe environment
- **Gradual Tuning**: Make small changes and test thoroughly
- **Data Logging**: Record flights for analysis and debugging
- **Backup Configuration**: Save working parameter sets

## 🔬 Research Applications

This system is designed for research in:
- **Control Theory**: Advanced PID and adaptive control
- **Robotics**: Autonomous flight and navigation
- **Machine Learning**: Reinforcement learning for control
- **System Identification**: Automatic model fitting and analysis
- **Real-time Systems**: Low-latency communication and control

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

---

**Note**: This system is designed for research and educational purposes. Always follow local regulations and safety guidelines when operating drones. 