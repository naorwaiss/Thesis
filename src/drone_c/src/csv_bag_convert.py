import os
import csv
import rclpy
from rclpy.serialization import deserialize_message
from rosidl_runtime_py.utilities import get_message
from rosbag2_py import SequentialReader, StorageOptions, ConverterOptions

def extract_rosbag_to_csv(bag_path, output_dir):
    rclpy.init()

    # Create the reader for the bag file
    reader = SequentialReader()
    storage_options = StorageOptions(uri=bag_path, storage_id='sqlite3')
    converter_options = ConverterOptions(input_serialization_format='cdr', output_serialization_format='cdr')
    reader.open(storage_options, converter_options)

    # Get the list of topics and their types
    topic_types = reader.get_all_topics_and_types()
    topics = {topic.name: get_message(topic.type) for topic in topic_types}

    # Create output directory if it doesn't exist
    os.makedirs(output_dir, exist_ok=True)

    # Prepare a CSV file for each topic
    writers = {}
    csv_files = {}

    for topic_name in topics.keys():
        csv_file_path = os.path.join(output_dir, f"{topic_name.replace('/', '_')}.csv")
        csv_file = open(csv_file_path, mode='w', newline='')
        writer = csv.writer(csv_file)

        # Write the header row for each topic
        writer.writerow(['timestamp', 'data'])
        writers[topic_name] = writer
        csv_files[topic_name] = csv_file

    while reader.has_next():
        (topic_name, serialized_data, timestamp) = reader.read_next()

        # Deserialize the message
        msg_type = topics[topic_name]
        message = deserialize_message(serialized_data, msg_type)

        # Write data to the respective topic's CSV file
        writers[topic_name].writerow([timestamp, str(message)])

    # Close all CSV files
    for csv_file in csv_files.values():
        csv_file.close()

    rclpy.shutdown()

if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description="Extract ROS2 bag data into separate CSV files for each topic.")
    parser.add_argument('--bag', required=True, help="Path to the ROS2 bag file")
    parser.add_argument('--output', required=True, help="Directory to save the output CSV files")

    args = parser.parse_args()

    extract_rosbag_to_csv(args.bag, args.output)
