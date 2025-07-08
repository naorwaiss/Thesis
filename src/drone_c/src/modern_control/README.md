# Drone Control Modern

A ROS2-based drone control system with modern control analysis capabilities.

## Features

- Real-time drone data collection and buffering
- Control system analysis with step response characteristics
- Second-order system fitting and analysis
- Support for both rate and stabilize control modes
- ROS2 integration for drone communication

## Installation

### Prerequisites

- Python 3.8 or higher
- ROS2 (Humble or later)
- pip

### Install the package

```bash
# Clone the repository
git clone <your-repository-url>
cd drone-control-modern

# Install in development mode
pip install -e .

# Or install in production mode
pip install .
```

### Install with development dependencies

```bash
pip install -e .[dev]
```

## Usage

### Basic Usage

```python
from src.control import ControlAnalyzer

# Create a control analyzer
analyzer = ControlAnalyzer(data_hz=50)

# Analyze step response
results = analyzer.analyze_step_response(desired_data, actual_data, "system_name")
```

### Running the main application

```bash
# Run the main drone control application
python main.py

# Or use the console script (if installed)
drone-control
```

## Dependencies

- rclpy >= 4.0.0
- sensor_msgs
- std_msgs
- numpy >= 1.21.0
- scipy >= 1.7.0

## Development

### Running tests

```bash
pytest
```

### Code formatting

```bash
black .
```

### Linting

```bash
flake8 .
```

## License

MIT License

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## Contact

- Author: Your Name
- Email: your.email@example.com 