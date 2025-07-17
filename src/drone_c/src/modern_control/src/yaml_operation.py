import yaml

class yaml_flash():
    def __init__(self, file_path):
        self.file_path = file_path
        self.data = self.load_data()

    def load_data(self):
        try:
            with open(self.file_path, 'r') as file:
                return yaml.safe_load(file)
        except FileNotFoundError:
            # Create directory if it doesn't exist
            import os
            os.makedirs(os.path.dirname(self.file_path), exist_ok=True)
            # Return empty dict if file doesn't exist
            return {}
        except Exception as e:
            print(f"Error loading YAML file: {e}")
            return {}
    
    def clear_file(self):
        try:
            with open(self.file_path, 'w') as file:
                file.truncate(0)
        except Exception as e:
            print(f"Error clearing file: {e}")

    def write_data(self, name, data, length):
        try:
            # Create directory if it doesn't exist
            import os
            os.makedirs(os.path.dirname(self.file_path), exist_ok=True)
            
            # Create a dictionary with the data
            yaml_data = {
                name: {
                    'data': data,
                    'length': length
                }
            }
            
            with open(self.file_path, 'a') as file:
                yaml.dump(yaml_data, file, default_flow_style=False)
        except Exception as e:
            print(f"Error writing data: {e}")
