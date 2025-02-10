#############################################finding D freq###########################

# import rclpy
# from rosbag2_py import SequentialReader, StorageOptions, ConverterOptions
# from rclpy.serialization import deserialize_message
# from rosidl_runtime_py.utilities import get_message

# import numpy as np
# import matplotlib.pyplot as plt
# from scipy.signal import butter, filtfilt

# # Function to extract `d_roll` data from a bag file
# def extract_d_roll(bag_path, topic_name='/PID_rate'):
#     storage_options = StorageOptions(
#         uri=bag_path,
#         storage_id='sqlite3'
#     )
#     converter_options = ConverterOptions(
#         input_serialization_format='cdr',
#         output_serialization_format='cdr'
#     )
#     reader = SequentialReader()
#     reader.open(storage_options, converter_options)

#     # Get the message type for the topic
#     topic_type_map = {topic.name: topic.type for topic in reader.get_all_topics_and_types()}
#     if topic_name not in topic_type_map:
#         raise ValueError(f"Topic {topic_name} not found in the bag file.")

#     message_type_str = topic_type_map[topic_name]
#     message_type = get_message(message_type_str)

#     d_roll_data = []
#     timestamps = []  # To store timestamps for computing sampling frequency
#     while reader.has_next():
#         topic, data, timestamp = reader.read_next()
#         if topic == topic_name:
#             # Deserialize the message
#             message = deserialize_message(data, message_type)
#             d_roll_data.append(message.d_roll)  # Adjust field access as per your message type
#             timestamps.append(timestamp)

#     # Compute the sampling frequency
#     timestamps = np.array(timestamps)
#     if len(timestamps) > 1:
#         time_deltas = np.diff(timestamps) * 1e-9  # Convert nanoseconds to seconds
#         fs = 1 / np.mean(time_deltas)
#     else:
#         fs = None  # Insufficient data to compute sampling frequency

#     return d_roll_data, fs

# # Function to plot the frequency spectrum
# def plot_frequency_spectrum(data, fs):
#     if fs is None:
#         raise ValueError("Sampling frequency (fs) is required to compute the frequency spectrum.")
    
#     n = len(data)
#     fft_values = np.fft.fft(data)
#     fft_freqs = np.fft.fftfreq(n, 1/fs)
#     magnitude = np.abs(fft_values[:n//2])  # One-sided spectrum

#     plt.figure(figsize=(10, 6))
#     plt.plot(fft_freqs[:n//2], magnitude)
#     plt.title('Frequency Spectrum of d_roll')
#     plt.xlabel('Frequency (Hz)')
#     plt.ylabel('Magnitude')
#     plt.grid()
#     plt.show()

# # Main code
# if __name__ == '__main__':
#     # Path to the bag file
#     bag_path = '/home/naor/Desktop/naor/study/hamama/rosbag2_2025_01_04-19_13_11/rosbag2_2025_01_04-19_13_11_0.db3'
#     topic_name = '/PID_rate'

#     # Step 1: Extract `d_roll` data
#     d_roll, fs = extract_d_roll(bag_path, topic_name)

#     # Step 2: Plot raw `d_roll` data
#     plt.figure(figsize=(10, 6))
#     plt.plot(d_roll, label='Raw d_roll')
#     plt.xlabel('Sample Index')
#     plt.ylabel('d_roll')
#     plt.title('Raw d_roll Data')
#     plt.legend()
#     plt.grid()
#     plt.show()

#     # Step 3: Plot the frequency spectrum of `d_roll`
#     if fs is not None:
#         plot_frequency_spectrum(d_roll, fs)
#     else:
#         print("Insufficient data to compute the frequency spectrum.")



# #########################################################euiler filter 


# import rclpy
# from rosbag2_py import SequentialReader, StorageOptions, ConverterOptions
# from rclpy.serialization import deserialize_message
# from rosidl_runtime_py.utilities import get_message

# import numpy as np
# import matplotlib.pyplot as plt

# # Function to extract data from a bag file
# def extract_euler_data(bag_path, topic_name='/euler_angles_data'):
#     storage_options = StorageOptions(
#         uri=bag_path,
#         storage_id='sqlite3'
#     )
#     converter_options = ConverterOptions(
#         input_serialization_format='cdr',
#         output_serialization_format='cdr'
#     )
#     reader = SequentialReader()
#     reader.open(storage_options, converter_options)

#     # Get the message type for the topic
#     topic_type_map = {topic.name: topic.type for topic in reader.get_all_topics_and_types()}
#     if topic_name not in topic_type_map:
#         raise ValueError(f"Topic {topic_name} not found in the bag file.")

#     message_type_str = topic_type_map[topic_name]
#     message_type = get_message(message_type_str)

#     data_pitch = []  # Pitch (first Euler angle)
#     data_roll = []   # Roll (second Euler angle)
#     timestamps = []  # To store timestamps for computing sampling frequency

#     while reader.has_next():
#         topic, data, timestamp = reader.read_next()
#         if topic == topic_name:
#             # Deserialize the message
#             message = deserialize_message(data, message_type)
#             data_pitch.append(message.pitch)
#             data_roll.append(message.roll)
#             timestamps.append(timestamp)

#     # Compute the sampling frequency
#     timestamps = np.array(timestamps)
#     if len(timestamps) > 1:
#         time_deltas = np.diff(timestamps) * 1e-9  # Convert nanoseconds to seconds
#         fs = 1 / np.mean(time_deltas)
#     else:
#         fs = None  # Insufficient data to compute sampling frequency

#     return data_pitch, data_roll, fs

# # Function to plot the frequency spectrum
# def plot_frequency_spectrum(data, fs, title):
#     if fs is None:
#         raise ValueError("Sampling frequency (fs) is required to compute the frequency spectrum.")
    
#     n = len(data)
#     fft_values = np.fft.fft(data)
#     fft_freqs = np.fft.fftfreq(n, 1/fs)
#     magnitude = np.abs(fft_values[:n//2])  # One-sided spectrum

#     plt.figure(figsize=(10, 6))
#     plt.plot(fft_freqs[:n//2], magnitude)
#     plt.title(f'Frequency Spectrum of {title}')
#     plt.xlabel('Frequency (Hz)')
#     plt.ylabel('Magnitude')
#     plt.grid()
#     plt.show()

# # Main code
# if __name__ == '__main__':
#     # Path to the bag file
#     bag_path = '/home/naor/Desktop/naor/study/hamama/src/drone_c/src/ros_bag/freestyle/rosbag2_2025_01_17-13_30_46_0.db3'
#     topic_name = '/euler_angles_data'

#     # Step 1: Extract Euler data
#     data1, data2, fs = extract_euler_data(bag_path, topic_name)
#     print(f"Calculated Sampling Frequency: {fs} Hz")

#     # Step 2: Plot raw data
#     plt.figure(figsize=(10, 6))
#     plt.plot(data1, label='First Euler Angle (data1)')
#     plt.plot(data2, label='Second Euler Angle (data2)')
#     plt.xlabel('Sample Index')
#     plt.ylabel('Value')
#     plt.title('Raw Euler Angles Data')
#     plt.legend()
#     plt.grid()
#     plt.show()

#     # Step 3: Plot the frequency spectrum
#     if fs is not None:
#         plot_frequency_spectrum(data1, fs, 'First Euler Angle (Raw)')
#         plot_frequency_spectrum(data2, fs, 'Second Euler Angle (Raw)')
#     else:
#         print("Insufficient data to compute the frequency spectrum.")





#####################################imu data raw##########################################
import rclpy
from rosbag2_py import SequentialReader, StorageOptions, ConverterOptions
from rclpy.serialization import deserialize_message
from rosidl_runtime_py.utilities import get_message

import numpy as np
import matplotlib.pyplot as plt

# Function to extract IMU data from a bag file
def extract_imu_data(bag_path, topic_name='/pololu_imu_data'):
    storage_options = StorageOptions(
        uri=bag_path,
        storage_id='sqlite3'
    )
    converter_options = ConverterOptions(
        input_serialization_format='cdr',
        output_serialization_format='cdr'
    )
    reader = SequentialReader()
    reader.open(storage_options, converter_options)

    # Get the message type for the topic
    topic_type_map = {topic.name: topic.type for topic in reader.get_all_topics_and_types()}
    if topic_name not in topic_type_map:
        raise ValueError(f"Topic {topic_name} not found in the bag file.")

    message_type_str = topic_type_map[topic_name]
    message_type = get_message(message_type_str)

    lin_acc_x, lin_acc_y, lin_acc_z = [], [], []
    ang_vel_x, ang_vel_y, ang_vel_z = [], [], []

    while reader.has_next():
        topic, data, _ = reader.read_next()
        if topic == topic_name:
            # Deserialize the message
            message = deserialize_message(data, message_type)
            lin_acc_x.append(message.linear_acceleration.x)
            lin_acc_y.append(message.linear_acceleration.y)
            lin_acc_z.append(message.linear_acceleration.z)
            ang_vel_x.append(message.angular_velocity.x)
            ang_vel_y.append(message.angular_velocity.y)
            ang_vel_z.append(message.angular_velocity.z)

    return lin_acc_x, lin_acc_y, lin_acc_z, ang_vel_x, ang_vel_y, ang_vel_z

# Function to extract magnetic field data from a bag file
def extract_magnetic_data(bag_path, topic_name='/magnetometer_data'):
    storage_options = StorageOptions(
        uri=bag_path,
        storage_id='sqlite3'
    )
    converter_options = ConverterOptions(
        input_serialization_format='cdr',
        output_serialization_format='cdr'
    )
    reader = SequentialReader()
    reader.open(storage_options, converter_options)

    # Get the message type for the topic
    topic_type_map = {topic.name: topic.type for topic in reader.get_all_topics_and_types()}
    if topic_name not in topic_type_map:
        raise ValueError(f"Topic {topic_name} not found in the bag file.")

    message_type_str = topic_type_map[topic_name]
    message_type = get_message(message_type_str)

    mag_x, mag_y, mag_z = [], [], []

    while reader.has_next():
        topic, data, _ = reader.read_next()
        if topic == topic_name:
            # Deserialize the message
            message = deserialize_message(data, message_type)
            mag_x.append(message.magnetic_field.x)
            mag_y.append(message.magnetic_field.y)
            mag_z.append(message.magnetic_field.z)

    return mag_x, mag_y, mag_z

# Function to compute magnitude
def compute_magnitude(x, y, z):
    return np.sqrt(np.array(x)**2 + np.array(y)**2 + np.array(z)**2)

# Function to compute FFT magnitude and corresponding frequencies
def compute_fft(data, sampling_rate):
    n = len(data)
    fft_values = np.fft.fft(data)
    fft_magnitude = np.abs(fft_values[:n // 2])
    fft_frequencies = np.fft.fftfreq(n, d=1/sampling_rate)[:n // 2]
    return fft_frequencies, fft_magnitude

# Main code
if __name__ == '__main__':
    # Path to the bag file
    bag_path = '/home/naor/Desktop/naor/study/hamama/src/drone_c/src/ros_bag/freestyle/rosbag2_2025_01_17-13_30_46_0.db3'
    topic_name_imu = '/pololu_imu_data'
    topic_name_mag = '/magnetometer_data'

    # Sampling rate (assumed, modify as necessary based on your system)
    sampling_rate = 100  # Hz

    # Step 1: Extract IMU data
    lin_acc_x, lin_acc_y, lin_acc_z, ang_vel_x, ang_vel_y, ang_vel_z = extract_imu_data(bag_path, topic_name_imu)

    # Step 2: Extract Magnetic Field data
    mag_x, mag_y, mag_z = extract_magnetic_data(bag_path, topic_name_mag)

    # Step 3: Compute FFT for IMU data
    fft_freq_lin_x, fft_mag_lin_x = compute_fft(lin_acc_x, sampling_rate)
    fft_freq_lin_y, fft_mag_lin_y = compute_fft(lin_acc_y, sampling_rate)
    fft_freq_lin_z, fft_mag_lin_z = compute_fft(lin_acc_z, sampling_rate)

    fft_freq_ang_x, fft_mag_ang_x = compute_fft(ang_vel_x, sampling_rate)
    fft_freq_ang_y, fft_mag_ang_y = compute_fft(ang_vel_y, sampling_rate)
    fft_freq_ang_z, fft_mag_ang_z = compute_fft(ang_vel_z, sampling_rate)

    # Step 4: Compute FFT for Magnetic Field data
    fft_freq_mag_x, fft_mag_mag_x = compute_fft(mag_x, sampling_rate)
    fft_freq_mag_y, fft_mag_mag_y = compute_fft(mag_y, sampling_rate)
    fft_freq_mag_z, fft_mag_mag_z = compute_fft(mag_z, sampling_rate)

    # Step 5: Plot the FFT results
    plt.figure(figsize=(15, 20))

    # Linear acceleration FFT
    plt.subplot(5, 2, 1)
    plt.plot(fft_freq_lin_x, fft_mag_lin_x, label='Linear Acceleration X')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Linear Acceleration X')
    plt.legend()
    plt.grid()

    plt.subplot(5, 2, 3)
    plt.plot(fft_freq_lin_y, fft_mag_lin_y, label='Linear Acceleration Y')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Linear Acceleration Y')
    plt.legend()
    plt.grid()

    plt.subplot(5, 2, 5)
    plt.plot(fft_freq_lin_z, fft_mag_lin_z, label='Linear Acceleration Z')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Linear Acceleration Z')
    plt.legend()
    plt.grid()

    # Angular velocity FFT
    plt.subplot(5, 2, 2)
    plt.plot(fft_freq_ang_x, fft_mag_ang_x, label='Angular Velocity X')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Angular Velocity X')
    plt.legend()
    plt.grid()

    plt.subplot(5, 2, 4)
    plt.plot(fft_freq_ang_y, fft_mag_ang_y, label='Angular Velocity Y')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Angular Velocity Y')
    plt.legend()
    plt.grid()

    plt.subplot(5, 2, 6)
    plt.plot(fft_freq_ang_z, fft_mag_ang_z, label='Angular Velocity Z')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Angular Velocity Z')
    plt.legend()
    plt.grid()

    # Magnetic field FFT
    plt.subplot(5, 2, 7)
    plt.plot(fft_freq_mag_x, fft_mag_mag_x, label='Magnetic Field X')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Magnetic Field X')
    plt.legend()
    plt.grid()

    plt.subplot(5, 2, 8)
    plt.plot(fft_freq_mag_y, fft_mag_mag_y, label='Magnetic Field Y')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Magnetic Field Y')
    plt.legend()
    plt.grid()

    plt.subplot(5, 2, 9)
    plt.plot(fft_freq_mag_z, fft_mag_mag_z, label='Magnetic Field Z')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.title('FFT of Magnetic Field Z')
    plt.legend()
    plt.grid()

    plt.tight_layout()
    plt.suptitle('Frequency Analysis of IMU and Magnetic Field Data (Noise Analysis)', y=1.02)
    plt.show()