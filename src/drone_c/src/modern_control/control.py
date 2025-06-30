
import time
import threading
import numpy as np
from scipy.optimize import curve_fit


class ControlAnalyzer:
    """Class responsible for control system analysis and printing"""
    
    def __init__(self, data_hz=100):
        self.data_hz = data_hz

    def analyze_step_response(self, desired, actual, name):
        """Analyze step response characteristics"""
        if len(desired) != len(actual) or len(actual) < 10:
            return None
            
        desired = np.array(desired)
        actual = np.array(actual)
        
        # Find step change
        step_change = np.diff(desired)
        step_indices = np.where(np.abs(step_change) > 0.1)[0]
        
        if len(step_indices) == 0:
            return None
            
        # Use the first significant step
        step_idx = step_indices[0]
        if step_idx + 50 >= len(actual):
            return None
            
        # Extract response data
        response = actual[step_idx:step_idx + 50]
        time_data = np.arange(len(response)) / self.data_hz
        final_value = desired[step_idx + 49]  # Target value
        
        # Calculate characteristics
        initial_value = response[0]
        step_magnitude = final_value - initial_value
        
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
            'final_value': final_value
        }

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

    def perform_analysis(self, rate_data, stab_data):
        """Perform control system analysis and print results"""
        results = {}
        
        # Analyze rate control if buffer is full
        if rate_data['is_full'] and len(rate_data['actual_x']) > 10:
            results['rate_x'] = self.analyze_step_response(
                rate_data['desired_x'],
                rate_data['actual_x'],
                "Rate X"
            )
            
        if rate_data['is_full'] and len(rate_data['actual_y']) > 10:
            results['rate_y'] = self.analyze_step_response(
                rate_data['desired_y'],
                rate_data['actual_y'],
                "Rate Y"
            )
        
        # Analyze stabilize control if buffer is full
        if stab_data['is_full'] and len(stab_data['actual_roll']) > 10:
            results['stab_roll'] = self.analyze_step_response(
                stab_data['desired_x'],
                stab_data['actual_roll'],
                "Stabilize Roll"
            )
            
        if stab_data['is_full'] and len(stab_data['actual_pitch']) > 10:
            results['stab_pitch'] = self.analyze_step_response(
                stab_data['desired_y'],
                stab_data['actual_pitch'],
                "Stabilize Pitch"
            )
        
        # Print analysis results
        self.print_analysis_results(results)
        
        # Perform second-order system fitting
        self.perform_second_order_analysis(results)
        
        return results

    def print_analysis_results(self, results):
        """Print analysis results to console"""
        if not results:
            return
            
        print("\n" + "="*60)
        print("CONTROL SYSTEM ANALYSIS RESULTS")
        print("="*60)
        
        for key, result in results.items():
            if result is None:
                continue
                
            print(f"\n--- {result['name']} ---")
            if result['rise_time']:
                print(f"Rise Time (10%-90%): {result['rise_time']:.3f} s")
            else:
                print("Rise Time: N/A")
                
            if result['settling_time']:
                print(f"Settling Time (5%): {result['settling_time']:.3f} s")
            else:
                print("Settling Time: N/A")
                
            print(f"Overshoot: {result['overshoot']:.2f}%")
            print(f"Steady-State Error: {result['steady_state_error']:.4f}")
            print(f"Step Magnitude: {result['step_magnitude']:.4f}")

    def perform_second_order_analysis(self, results):
        """Perform and print second-order system analysis"""
        if not results:
            return
            
        print("\n" + "="*60)
        print("SECOND-ORDER SYSTEM ANALYSIS")
        print("="*60)
        
        for key, result in results.items():
            if result is None:
                continue
                
            print(f"\n--- {result['name']} ---")
            
            # Fit second-order system
            second_order_result = self.fit_second_order_system(
                result['response_data'],
                result['time_data'],
                result['final_value'],
                result['name']
            )
            
            if second_order_result:
                print(f"DC Gain (K): {second_order_result['K']:.3f}")
                print(f"Damping Ratio (ζ): {second_order_result['zeta']:.3f}")
                print(f"Natural Frequency (ωn): {second_order_result['omega_n']:.2f} rad/s")
                print(f"Natural Frequency (fn): {second_order_result['omega_n']/(2*np.pi):.2f} Hz")
                
                if second_order_result['omega_d']:
                    print(f"Damped Frequency (ωd): {second_order_result['omega_d']:.2f} rad/s")
                    print(f"Theoretical Rise Time: {second_order_result['rise_time_theory']:.3f} s")
                    print(f"Theoretical Overshoot: {second_order_result['overshoot_theory']:.2f}%")
                
                print(f"Theoretical Settling Time: {second_order_result['settling_time_theory']:.3f} s")
                print(f"System Type: {second_order_result['system_type']}")
            else:
                print("Second-order system fitting failed")
        
        print("\n" + "="*60)
