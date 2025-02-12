import os
from evdev import InputDevice, list_devices
from launch import LaunchDescription
from launch_ros.actions import Node

# Define the specific joysticks to detect by their exact names and topic names
VALID_JOYSTICKS = {
    "Logitech Extreme 3D Pro": "joy_logitech_extreme_3d_pro",
    "EdgeTX RadioMaster Pocket Joystick": "joy_edgetx_radiomaster_pocket",
    "Logitech Gamepad F710": "joy_logitech_gamepad_f710",
}

def find_unique_joysticks():
    """Find and register each specific joystick type once, ensuring no duplicate assignment."""
    devices = [InputDevice(dev) for dev in list_devices()]
    detected_joysticks = {}  # Store detected joysticks with their paths
    used_physical_devices = set()  # Track physical device paths that have been assigned

    for dev in devices:
        print(f"[DEBUG] Checking device: {dev.name} ({dev.path})")
        
        # Get unique physical identifier (combination of vendor ID and product ID)
        physical_id = f"{dev.info.vendor:04x}:{dev.info.product:04x}"
        
        # Ensure exact match for joystick name and not already used
        if dev.name.strip() in VALID_JOYSTICKS and physical_id not in used_physical_devices:
            topic_name = VALID_JOYSTICKS[dev.name.strip()]
            
            # Store both the device path and mark this physical device as used
            detected_joysticks[topic_name] = {
                'path': dev.path,
                'physical_id': physical_id,
                'name': dev.name.strip()
            }
            used_physical_devices.add(physical_id)
            print(f"[INFO] Matched {dev.name} → {topic_name} at {dev.path} (ID: {physical_id})")
        else:
            if physical_id in used_physical_devices:
                print(f"[INFO] Skipping duplicate device: {dev.name} ({physical_id})")

    return detected_joysticks

def generate_launch_description():
    """Generate a launch description for only detected joysticks."""
    joysticks = find_unique_joysticks()

    if not joysticks:
        print("[WARNING] No valid joysticks detected. No joy_node will be launched.")
        return LaunchDescription([])

    joy_nodes = []
    for topic_name, device_info in joysticks.items():
        node_name = topic_name.replace("/", "")  # ROS node names cannot have '/'

        print(f"[INFO] Creating joy_node for {device_info['name']} on topic /{topic_name}")
        print(f"       Device path: {device_info['path']}")
        print(f"       Physical ID: {device_info['physical_id']}")

        joy_nodes.append(
            Node(
                package='joy',
                executable='joy_node',
                name=node_name,
                namespace=node_name,
                remappings=[('/joy', f"/{topic_name}/joy")],
                parameters=[{
                    'dev': device_info['path'],
                    'deadzone': 0.05,
                    'autorepeat_rate': 20.0,
                    'use_sim_time': False,
                }],
                output='screen'
            )
        )

    return LaunchDescription(joy_nodes)

if __name__ == '__main__':
    generate_launch_description()