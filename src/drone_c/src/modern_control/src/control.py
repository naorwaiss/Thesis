import time
import threading
import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt


class ControlAnalyzer:
    """Class responsible for control system analysis and printing"""

    def __init__(self, data_hz=50):
        self.data_hz = data_hz
        self.return_data_step = None
        self.return_data_second = None

    def analyze_step_response(self, desired, actual, name, step_threshold=0.1):
        print(f"start the step part for {name}")
        """Analyze step response characteristics"""

        data_length = len(desired)
        analysis_window = int(data_length * 0.4)  # Reduced from 0.6 to 0.4
        print(f"Data length: {data_length}, Analysis window: {analysis_window}")
        
        # 1. Step Response Analysi
        try:
            # Input validation
            if len(desired) != len(actual) or len(actual) < analysis_window:
                print(f"Warning: Insufficient data for {name}. Desired: {len(desired)}, Actual: {len(actual)}, Required: {analysis_window}")
                return None

            desired = np.array(desired)
            actual = np.array(actual)

            # Check for valid data (no NaN or inf values)
            if np.any(np.isnan(desired)) or np.any(np.isnan(actual)) or np.any(np.isinf(desired)) or np.any(np.isinf(actual)):
                print(f"Warning: Invalid data (NaN or inf) detected for {name}")
                return None

            # Find step change
            step_change = np.diff(desired)
            step_indices = np.where(np.abs(step_change) > step_threshold)[0]
            print(f"Found {len(step_indices)} step changes for {name}")

            if len(step_indices) == 0:
                print(f"Warning: No significant step detected for {name} (threshold: {step_threshold})")
                return None

            # Use the first significant step
            step_idx = step_indices[0]
            print(f"Using step at index {step_idx} for {name}")
            
            if step_idx + analysis_window >= len(actual):
                print(f"Warning: Insufficient data after step for {name}. Step at {step_idx}, need {analysis_window} points, have {len(actual) - step_idx}")
                return None

            # Extract response data
            response = actual[step_idx:step_idx + analysis_window]
            time_data = np.arange(len(response)) / self.data_hz

            # Use the last desired value as final value (more robust)
            final_value = desired[step_idx + analysis_window - 1] if step_idx + \
                analysis_window - 1 < len(desired) else desired[-1]

            # Calculate characteristics
            initial_value = response[0]
            step_magnitude = final_value - initial_value

            # Check if step magnitude is significant
            if abs(step_magnitude) < step_threshold:
                print(f"Warning: Step magnitude too small for {name}: {step_magnitude}")
                return None

            # Rise time (10% to 90%)
            rise_10 = initial_value + 0.1 * step_magnitude
            rise_90 = initial_value + 0.9 * step_magnitude

            rise_10_idx = np.where(response >= rise_10)[0]
            rise_90_idx = np.where(response >= rise_90)[0]

            rise_time = None
            if len(rise_10_idx) > 0 and len(rise_90_idx) > 0:
                rise_time = (rise_90_idx[0] - rise_10_idx[0]) / self.data_hz

            # Settling time (within 5% of final value)
            settling_threshold = 0.05 * abs(step_magnitude)
            settled_indices = np.where(np.abs(response - final_value) <= settling_threshold)[0]

            settling_time = None
            if len(settled_indices) > 0:
                settling_time = settled_indices[0] / self.data_hz

            # Overshoot
            max_value = np.max(response)
            overshoot = ((max_value - final_value) / step_magnitude) * 100 if step_magnitude > 0 else 0

            # Steady-state error
            steady_state_error = final_value - response[-1]

            return {
                'name': name,
                'rise_time': rise_time,
                'settling_time': settling_time,
                'overshoot': overshoot,
                'steady_state_error': steady_state_error,
                'step_magnitude': step_magnitude,
                'response_data': response,
                'time_data': time_data,
                'final_value': final_value,
                'initial_value': initial_value
            }

        except Exception as e:
            print(f"Error in step response analysis for {name}: {str(e)}")
            return None

    def fit_second_order_system(self, response_data, time_data, final_value, name):
        """Fit second-order system to the data"""
        # Second-order transfer function: G(s) = K * ωn² / (s² + 2ζωn*s + ωn²)
        def second_order_response(t, K, zeta, omega_n):
            if zeta < 1:  # Underdamped
                omega_d = omega_n * np.sqrt(1 - zeta**2)
                return K * (1 - np.exp(-zeta * omega_n * t) *
                            (np.cos(omega_d * t) + zeta * omega_n / omega_d * np.sin(omega_d * t)))
            elif zeta == 1:  # Critically damped
                return K * (1 - (1 + omega_n * t) * np.exp(-omega_n * t))
            else:  # Overdamped
                omega_d = omega_n * np.sqrt(zeta**2 - 1)
                return K * (1 - (zeta * omega_n + omega_d) / (2 * omega_d) *
                            np.exp(-(zeta * omega_n - omega_d) * t) +
                            (zeta * omega_n - omega_d) / (2 * omega_d) *
                            np.exp(-(zeta * omega_n + omega_d) * t))

        # Normalize response to unit step
        normalized_response = (response_data - response_data[0]) / (final_value - response_data[0])

        # Initial parameter estimates
        K = 1.0  # DC gain
        zeta_est = 0.7  # Damping ratio estimate
        omega_n_est = 10.0  # Natural frequency estimate

        try:
            # Fit the second-order system
            popt, pcov = curve_fit(second_order_response, time_data, normalized_response,
                                   p0=[K, zeta_est, omega_n_est],
                                   bounds=([0.5, 0.1, 1.0], [2.0, 2.0, 50.0]))

            K_fit, zeta_fit, omega_n_fit = popt

            # Calculate theoretical characteristics
            if zeta_fit < 1:  # Underdamped
                omega_d = omega_n_fit * np.sqrt(1 - zeta_fit**2)
                rise_time_theory = (np.pi - np.arccos(zeta_fit)) / omega_d
                settling_time_theory = 4 / (zeta_fit * omega_n_fit)
                overshoot_theory = np.exp(-zeta_fit * np.pi / np.sqrt(1 - zeta_fit**2)) * 100
            else:  # Critically damped or overdamped
                rise_time_theory = None
                settling_time_theory = 4 / (zeta_fit * omega_n_fit)
                overshoot_theory = 0

            return {
                'K': K_fit,
                'zeta': zeta_fit,
                'omega_n': omega_n_fit,
                'omega_d': omega_d if zeta_fit < 1 else None,
                'rise_time_theory': rise_time_theory,
                'settling_time_theory': settling_time_theory,
                'overshoot_theory': overshoot_theory,
                'system_type': 'Underdamped' if zeta_fit < 1 else 'Critically Damped' if zeta_fit == 1 else 'Overdamped'
            }

        except Exception as e:
            print(f"Second-order fit failed for {name}: {str(e)}")
            return None

    def secend_response_Data(self, desired, actual, name):
        """
        Analyze second-order response characteristics

        Returns:
            dict: Dictionary containing analysis results
        """

        self.return_data_step = self.analyze_step_response(desired, actual, name)
        self.return_data_second = self.fit_second_order_system(
            self.return_data_step['response_data'], self.return_data_step['time_data'], self.return_data_step['final_value'], name)
        print(f"name: {name}, K: {self.return_data_second['K']}, zeta: {self.return_data_second['zeta']}, omega_n: {self.return_data_second['omega_n']}, omega_d: {self.return_data_second['omega_d'] if self.return_data_second['zeta'] < 1 else None}, rise_time_theory: {self.return_data_second['rise_time_theory']}, settling_time_theory: {self.return_data_second['settling_time_theory']}, overshoot_theory: {self.return_data_second['overshoot_theory']}, system_type: {'Underdamped' if self.return_data_second['zeta'] < 1 else 'Critically Damped' if self.return_data_second['zeta'] == 1 else 'Overdamped'}")

