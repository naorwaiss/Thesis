from PyQt5.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QLabel, QLineEdit, QPushButton, QTextEdit, QGridLayout, QGroupBox
from PyQt5.QtCore import QTimer, pyqtSignal
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.pyplot as plt
import numpy as np
from collections import deque
import time


class ControlVisualizer(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.initData()
        self.initTimer()

    def initData(self):
        """Initialize data buffers for plotting"""
        self.max_points = 500
        self.time_data = deque(maxlen=self.max_points)
        self.desired_rate_x = deque(maxlen=self.max_points)
        self.actual_rate_x = deque(maxlen=self.max_points)
        self.desired_rate_y = deque(maxlen=self.max_points)
        self.actual_rate_y = deque(maxlen=self.max_points)
        self.error_x = deque(maxlen=self.max_points)
        self.error_y = deque(maxlen=self.max_points)
        self.pid_gains = deque(maxlen=self.max_points)
        self.performance_scores = deque(maxlen=self.max_points)
        
        # Initialize time counter
        self.start_time = time.time()

    def initTimer(self):
        """Initialize timer for real-time updates"""
        self.timer = QTimer()
        self.timer.timeout.connect(self.updatePlots)
        self.timer.start(100)  # Update every 100ms

    def initUI(self):
        self.setWindowTitle('Control Visualizer - 4 Panel Layout')
        self.setGeometry(100, 100, 1200, 800)

        # Create main layout
        main_layout = QVBoxLayout()
        
        # Create header
        header_layout = QHBoxLayout()
        title_label = QLabel('Control Visualizer - Real-time PID Learning')
        title_label.setStyleSheet("font-size: 16px; font-weight: bold; color: #2c3e50;")
        header_layout.addWidget(title_label)
        header_layout.addStretch()
        
        # Add control buttons
        self.start_button = QPushButton('Start Learning')
        self.stop_button = QPushButton('Stop Learning')
        self.clear_button = QPushButton('Clear Plots')
        self.save_button = QPushButton('Save Data')
        
        header_layout.addWidget(self.start_button)
        header_layout.addWidget(self.stop_button)
        header_layout.addWidget(self.clear_button)
        header_layout.addWidget(self.save_button)
        
        main_layout.addLayout(header_layout)
        
        # Create 4-panel grid layout
        grid_layout = QGridLayout()
        
        # Panel 1: Rate Control Performance (X-axis)
        self.panel1 = self.createRateControlPanel("X-Axis Rate Control", "roll")
        grid_layout.addWidget(self.panel1, 0, 0)
        
        # Panel 2: Rate Control Performance (Y-axis)
        self.panel2 = self.createRateControlPanel("Y-Axis Rate Control", "pitch")
        grid_layout.addWidget(self.panel2, 0, 1)
        
        # Panel 3: PID Gains Learning
        self.panel3 = self.createPIDGainsPanel()
        grid_layout.addWidget(self.panel3, 1, 0)
        
        # Panel 4: Performance Metrics
        self.panel4 = self.createPerformancePanel()
        grid_layout.addWidget(self.panel4, 1, 1)
        
        main_layout.addLayout(grid_layout)
        
        # Add status bar
        status_layout = QHBoxLayout()
        self.status_label = QLabel('Status: Ready')
        self.status_label.setStyleSheet("color: #27ae60; font-weight: bold;")
        status_layout.addWidget(self.status_label)
        status_layout.addStretch()
        
        # Add performance indicators
        self.performance_label = QLabel('Performance Score: 0.00')
        self.gains_label = QLabel('Current Gains - Kp_x: 0.000, Kp_y: 0.000')
        status_layout.addWidget(self.performance_label)
        status_layout.addWidget(self.gains_label)
        
        main_layout.addLayout(status_layout)
        
        self.setLayout(main_layout)
        
        # Connect buttons
        self.start_button.clicked.connect(self.startLearning)
        self.stop_button.clicked.connect(self.stopLearning)
        self.clear_button.clicked.connect(self.clearPlots)
        self.save_button.clicked.connect(self.saveData)

    def createRateControlPanel(self, title, axis):
        """Create a rate control panel with matplotlib plot"""
        group_box = QGroupBox(title)
        layout = QVBoxLayout()
        
        # Create matplotlib figure
        fig = Figure(figsize=(6, 4), dpi=100)
        canvas = FigureCanvas(fig)
        ax = fig.add_subplot(111)
        
        # Initialize plot
        ax.set_xlabel('Time (s)')
        ax.set_ylabel('Rate (rad/s)')
        ax.set_title(f'{title} - Real-time')
        ax.grid(True, alpha=0.3)
        
        # Create plot lines
        line_desired, = ax.plot([], [], 'b-', label='Desired', linewidth=2)
        line_actual, = ax.plot([], [], 'r-', label='Actual', linewidth=2)
        line_error, = ax.plot([], [], 'g--', label='Error', linewidth=1, alpha=0.7)
        
        ax.legend()
        fig.tight_layout()
        
        layout.addWidget(canvas)
        
        # Store references
        group_box.canvas = canvas
        group_box.ax = ax
        group_box.line_desired = line_desired
        group_box.line_actual = line_actual
        group_box.line_error = line_error
        group_box.axis = axis
        
        group_box.setLayout(layout)
        return group_box

    def createPIDGainsPanel(self):
        """Create PID gains learning panel"""
        group_box = QGroupBox("PID Gains Learning")
        layout = QVBoxLayout()
        
        # Create matplotlib figure
        fig = Figure(figsize=(6, 4), dpi=100)
        canvas = FigureCanvas(fig)
        ax = fig.add_subplot(111)
        
        # Initialize plot
        ax.set_xlabel('Time (s)')
        ax.set_ylabel('Gain Value')
        ax.set_title('PID Gains - Learning Progress')
        ax.grid(True, alpha=0.3)
        
        # Create plot lines
        line_kp_x, = ax.plot([], [], 'b-', label='Kp_x', linewidth=2)
        line_kp_y, = ax.plot([], [], 'r-', label='Kp_y', linewidth=2)
        
        ax.legend()
        fig.tight_layout()
        
        layout.addWidget(canvas)
        
        # Store references
        group_box.canvas = canvas
        group_box.ax = ax
        group_box.line_kp_x = line_kp_x
        group_box.line_kp_y = line_kp_y
        
        group_box.setLayout(layout)
        return group_box

    def createPerformancePanel(self):
        """Create performance metrics panel"""
        group_box = QGroupBox("Performance Metrics")
        layout = QVBoxLayout()
        
        # Create matplotlib figure
        fig = Figure(figsize=(6, 4), dpi=100)
        canvas = FigureCanvas(fig)
        ax = fig.add_subplot(111)
        
        # Initialize plot
        ax.set_xlabel('Time (s)')
        ax.set_ylabel('Performance Score')
        ax.set_title('Control Performance - Real-time')
        ax.grid(True, alpha=0.3)
        
        # Create plot line
        line_performance, = ax.plot([], [], 'purple', linewidth=2, label='Performance Score')
        
        ax.legend()
        fig.tight_layout()
        
        layout.addWidget(canvas)
        
        # Store references
        group_box.canvas = canvas
        group_box.ax = ax
        group_box.line_performance = line_performance
        
        group_box.setLayout(layout)
        return group_box

    def updatePlots(self):
        """Update all plots with new data"""
        current_time = time.time() - self.start_time
        
        # Generate simulated data (replace with real data from your system)
        if len(self.time_data) == 0:
            # Initialize with some data
            self.addSimulatedData()
        else:
            # Add new data point
            self.addSimulatedData()
        
        # Update Panel 1: X-axis Rate Control
        self.updateRateControlPanel(self.panel1, self.desired_rate_x, self.actual_rate_x, self.error_x)
        
        # Update Panel 2: Y-axis Rate Control
        self.updateRateControlPanel(self.panel2, self.desired_rate_y, self.actual_rate_y, self.error_y)
        
        # Update Panel 3: PID Gains
        self.updatePIDGainsPanel()
        
        # Update Panel 4: Performance
        self.updatePerformancePanel()
        
        # Update status
        self.updateStatus()

    def addSimulatedData(self):
        """Add simulated data for demonstration"""
        current_time = time.time() - self.start_time
        
        # Simulate desired rates (step inputs)
        if current_time < 5:
            desired_x, desired_y = 0.0, 0.0
        elif current_time < 10:
            desired_x, desired_y = 1.0, 0.0
        elif current_time < 15:
            desired_x, desired_y = 0.0, 1.0
        else:
            desired_x, desired_y = 0.5, 0.5
        
        # Simulate actual rates with some lag and noise
        if len(self.actual_rate_x) > 0:
            actual_x = self.actual_rate_x[-1] * 0.9 + desired_x * 0.1 + np.random.normal(0, 0.02)
            actual_y = self.actual_rate_y[-1] * 0.9 + desired_y * 0.1 + np.random.normal(0, 0.02)
        else:
            actual_x, actual_y = desired_x, desired_y
        
        # Calculate errors
        error_x = desired_x - actual_x
        error_y = desired_y - actual_y
        
        # Simulate PID gains (learning over time)
        if len(self.pid_gains) > 0:
            kp_x = self.pid_gains[-1][0] + np.random.normal(0, 0.01)
            kp_y = self.pid_gains[-1][1] + np.random.normal(0, 0.01)
        else:
            kp_x, kp_y = 1.0, 1.0
        
        # Calculate performance score
        performance_score = 10.0 - abs(error_x) - abs(error_y) - 0.1 * (kp_x + kp_y)
        
        # Add data to buffers
        self.time_data.append(current_time)
        self.desired_rate_x.append(desired_x)
        self.actual_rate_x.append(actual_x)
        self.desired_rate_y.append(desired_y)
        self.actual_rate_y.append(actual_y)
        self.error_x.append(error_x)
        self.error_y.append(error_y)
        self.pid_gains.append([kp_x, kp_y])
        self.performance_scores.append(performance_score)

    def updateRateControlPanel(self, panel, desired_data, actual_data, error_data):
        """Update rate control panel"""
        if len(self.time_data) < 2:
            return
        
        # Update plot data
        panel.line_desired.set_data(list(self.time_data), list(desired_data))
        panel.line_actual.set_data(list(self.time_data), list(actual_data))
        panel.line_error.set_data(list(self.time_data), list(error_data))
        
        # Update axis limits
        panel.ax.relim()
        panel.ax.autoscale_view()
        
        # Redraw
        panel.canvas.draw()

    def updatePIDGainsPanel(self):
        """Update PID gains panel"""
        if len(self.time_data) < 2 or len(self.pid_gains) < 2:
            return
        
        # Extract Kp values
        kp_x_values = [gains[0] for gains in self.pid_gains]
        kp_y_values = [gains[1] for gains in self.pid_gains]
        
        # Update plot data
        self.panel3.line_kp_x.set_data(list(self.time_data), kp_x_values)
        self.panel3.line_kp_y.set_data(list(self.time_data), kp_y_values)
        
        # Update axis limits
        self.panel3.ax.relim()
        self.panel3.ax.autoscale_view()
        
        # Redraw
        self.panel3.canvas.draw()

    def updatePerformancePanel(self):
        """Update performance panel"""
        if len(self.time_data) < 2 or len(self.performance_scores) < 2:
            return
        
        # Update plot data
        self.panel4.line_performance.set_data(list(self.time_data), list(self.performance_scores))
        
        # Update axis limits
        self.panel4.ax.relim()
        self.panel4.ax.autoscale_view()
        
        # Redraw
        self.panel4.canvas.draw()

    def updateStatus(self):
        """Update status information"""
        if len(self.pid_gains) > 0 and len(self.performance_scores) > 0:
            current_gains = self.pid_gains[-1]
            current_performance = self.performance_scores[-1]
            
            self.gains_label.setText(f'Current Gains - Kp_x: {current_gains[0]:.3f}, Kp_y: {current_gains[1]:.3f}')
            self.performance_label.setText(f'Performance Score: {current_performance:.2f}')

    def startLearning(self):
        """Start the learning process"""
        self.status_label.setText('Status: Learning Active')
        self.status_label.setStyleSheet("color: #e74c3c; font-weight: bold;")
        self.start_button.setEnabled(False)
        self.stop_button.setEnabled(True)

    def stopLearning(self):
        """Stop the learning process"""
        self.status_label.setText('Status: Learning Stopped')
        self.status_label.setStyleSheet("color: #f39c12; font-weight: bold;")
        self.start_button.setEnabled(True)
        self.stop_button.setEnabled(False)

    def clearPlots(self):
        """Clear all plots and data"""
        # Clear data buffers
        self.time_data.clear()
        self.desired_rate_x.clear()
        self.actual_rate_x.clear()
        self.desired_rate_y.clear()
        self.actual_rate_y.clear()
        self.error_x.clear()
        self.error_y.clear()
        self.pid_gains.clear()
        self.performance_scores.clear()
        
        # Reset start time
        self.start_time = time.time()
        
        # Clear plots
        for panel in [self.panel1, self.panel2, self.panel3, self.panel4]:
            panel.ax.clear()
            panel.ax.grid(True, alpha=0.3)
            panel.canvas.draw()
        
        # Reinitialize plot titles and labels
        self.panel1.ax.set_title('X-Axis Rate Control - Real-time')
        self.panel1.ax.set_xlabel('Time (s)')
        self.panel1.ax.set_ylabel('Rate (rad/s)')
        
        self.panel2.ax.set_title('Y-Axis Rate Control - Real-time')
        self.panel2.ax.set_xlabel('Time (s)')
        self.panel2.ax.set_ylabel('Rate (rad/s)')
        
        self.panel3.ax.set_title('PID Gains - Learning Progress')
        self.panel3.ax.set_xlabel('Time (s)')
        self.panel3.ax.set_ylabel('Gain Value')
        
        self.panel4.ax.set_title('Control Performance - Real-time')
        self.panel4.ax.set_xlabel('Time (s)')
        self.panel4.ax.set_ylabel('Performance Score')
        
        self.status_label.setText('Status: Plots Cleared')
        self.status_label.setStyleSheet("color: #27ae60; font-weight: bold;")

    def saveData(self):
        """Save current data to file"""
        import json
        from datetime import datetime
        
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = f"control_data_{timestamp}.json"
        
        data = {
            'timestamp': timestamp,
            'time_data': list(self.time_data),
            'desired_rate_x': list(self.desired_rate_x),
            'actual_rate_x': list(self.actual_rate_x),
            'desired_rate_y': list(self.desired_rate_y),
            'actual_rate_y': list(self.actual_rate_y),
            'error_x': list(self.error_x),
            'error_y': list(self.error_y),
            'pid_gains': list(self.pid_gains),
            'performance_scores': list(self.performance_scores)
        }
        
        with open(filename, 'w') as f:
            json.dump(data, f, indent=2)
        
        self.status_label.setText(f'Status: Data saved to {filename}')
        self.status_label.setStyleSheet("color: #27ae60; font-weight: bold;")


# Example usage
if __name__ == '__main__':
    import sys
    from PyQt5.QtWidgets import QApplication
    
    app = QApplication(sys.argv)
    visualizer = ControlVisualizer()
    visualizer.show()
    sys.exit(app.exec_())
        