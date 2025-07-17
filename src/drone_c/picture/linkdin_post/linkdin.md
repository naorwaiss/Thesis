Drone Control Thesis – End-to-End Open Source Development

Over the past year, Amit and I developed a fully open-source drone platform from the ground up, aimed at implementing and testing robust, advanced flight control algorithms beyond basic PID controllers.
The flight controller is based on a Teensy 4.1 microcontroller and a Pololu IMU, giving us full control over the hardware and software stack.

Unlike off-the-shelf solutions (e.g., ArduPilot), building the system ourselves gave us a unique opportunity to bridge the gap between theory and real-world engineering—applying knowledge from our academic background in a complex, multidisciplinary project.

Key areas we explored and developed:

✅ Custom PCB design for flight control and power distribution
✅ Hands-on understanding of discrete-time vs. continuous-time control, including firsthand experience with the challenges of numerical derivatives in discrete-time systems
✅ Precise timing and task scheduling in real-time embedded environments
✅ UDP communication with ROS, enabling live telemetry, in-flight tuning, and post-flight analysis via ROSBAG
✅ Design and tuning of filtering algorithms (Madgwick, low-pass), including FFT-based cutoff frequency selection
✅ IMU integration and calibration, involving deep dives into datasheets, ODR/full-scale config, and custom filtering
✅ Direct register-level programming for IMU and gyro configuration
✅ Advanced C++ and Python development using OOP principles

This experience gave us practical, hands-on insight into the challenges of building a full control system from the ground up—across both hardware and software layers.

We’re now transitioning to the next phase of the project: developing and testing more sophisticated and robust control methods for robotics and drone applications.
