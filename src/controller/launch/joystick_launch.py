import os
from evdev import InputDevice, list_devices
from launch import LaunchDescription
from launch_ros.actions import Node

def find_all_joysticks():
    """Find all joysticks using event devices."""
    devices = [InputDevice(dev) for dev in list_devices()]
    print("[DEBUG] Detected input devices:")
    joysticks = {}
    
    for dev in devices:
        print(f"  - Path: {dev.path}, Name: {dev.name}")
        # Look for joystick-like devices
        if any(keyword in dev.name.lower() for keyword in ["joystick", "gamepad", "extreme"]):
            # Use the event device directly
            joysticks[dev.path] = dev.name
            print(f"[DEBUG] Adding joystick: {dev.name} at {dev.path}")
    
    return joysticks

def generate_launch_description():
    """Generate a launch description that creates a joy_node for each detected joystick."""
    # Detect all connected joysticks
    joysticks = find_all_joysticks()
    
    if not joysticks:
        print("[WARNING] No joysticks detected. Please connect a joystick.")
    else:
        print("[INFO] Detected Joysticks:")
        for path, name in joysticks.items():
            print(f"  - {name} ({path})")
    
    # Create a joy_node for each detected joystick
    joy_nodes = []
    for path, name in joysticks.items():
        # Generate a unique topic name and node name based on device name
        base_name = name.replace(" ", "_").replace("-", "_").lower()
        device_id = os.path.basename(path).replace("event", "")
        topic_name = f"{base_name}_{device_id}"
        node_name = f"{topic_name}_node"
        
        print(f"[INFO] Creating joy_node for {name} on topic /{topic_name}")
        
        # Create a joy_node with appropriate parameters
        joy_nodes.append(
            Node(
                package='joy',
                executable='joy_node',
                name=node_name,
                remappings=[('/joy', f"/{topic_name}")],
                parameters=[{
                    'dev': path,
                    'deadzone': 0.05,
                    'autorepeat_rate': 20.0,
                }],
            )
        )
    
    return LaunchDescription(joy_nodes)

if __name__ == '__main__':
    generate_launch_description()
