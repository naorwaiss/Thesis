#include <Arduino.h>
#include "PID_type.h"
#include "Var_types.h"

#define ALPHA_LPF 0.6f
// attitude_t angle; // Attitude
// attitude_t angle_des; // Desired attitude
// attitude_t rate; // Attitude rate
// attitude_t rate_des; // Desired attitude rate
// attitude_t angle_err;  // Attitude error
attitude_t rate_err_HPF;
attitude_t rate_err_LPF;
attitude_t rate_err_clean;
// attitude_t rate_err = {0.0, 0.0, 0.0};
// attitude_t stab_err = {0.0, 0.0, 0.0};

// attitude_t angle_err_prev; // Previous attitude error
// attitude_t rate_err_prev; // Previous attitude rate error

PID_out_t rate_out, stab_out;  // Output of rate and stabilization controllers

PID_Params_t rate_params;  // PID parameters for rate controller
PID_Params_t stab_params;  // PID parameters for stabilization controller

// Initialization of PID parameters. Need to run at setup in the main code.
void initializePIDParams(float RrollPID[3] = nullptr, float RpitchPID[3] = nullptr, float RyawPID[3] = nullptr,
                         float Imax_rate[2] = nullptr, float SrollPID[3] = nullptr, float SpitchPID[3] = nullptr,
                         float SyawPID[3] = nullptr, float Imax_stab[2] = nullptr) {  // Rate mode parameters

    // Default ACRO mode parameter values
    const float defaultRrollPID[3] = {0.8f, 0.001f, 0.01f};
    const float defaultRpitchPID[3] = {1.2f, 0.001f, 0.01f};
    const float defaultRyawPID[3] = {2.0f, 0.0f, 0.01f};
    const float defaultImax_rate[2] = {100.0f, 100.0f};

    // Default STABILIZE mode parameter values
    const float defaultSrollPID[3] = {25.0f, 0.0f, 0.0f};
    const float defaultSpitchPID[3] = {25.0f, 0.0f, 0.0f};
    const float defaultSyawPID[3] = {4.0f, 0.0f, 0.0f};
    const float defaultImax_stab[2] = {100.0f, 100.0f};

    // Assign default values if nullptr is passed
    if (RrollPID == nullptr) RrollPID = const_cast<float*>(defaultRrollPID);
    if (RpitchPID == nullptr) RpitchPID = const_cast<float*>(defaultRpitchPID);
    if (RyawPID == nullptr) RyawPID = const_cast<float*>(defaultRyawPID);
    if (Imax_rate == nullptr) Imax_rate = const_cast<float*>(defaultImax_rate);
    if (SrollPID == nullptr) SrollPID = const_cast<float*>(defaultSrollPID);
    if (SpitchPID == nullptr) SpitchPID = const_cast<float*>(defaultSpitchPID);
    if (SyawPID == nullptr) SyawPID = const_cast<float*>(defaultSyawPID);
    if (Imax_stab == nullptr) Imax_stab = const_cast<float*>(defaultImax_stab);

    rate_params.RollP = RrollPID[0];
    rate_params.RollI = RrollPID[1];
    rate_params.RollD = RrollPID[2];
    rate_params.PitchP = RpitchPID[0];
    rate_params.PitchI = RpitchPID[1];
    rate_params.PitchD = RpitchPID[2];
    rate_params.YawP = RyawPID[0];
    rate_params.YawI = RyawPID[1];
    rate_params.YawD = RyawPID[2];
    rate_params.Imax_roll = Imax_rate[0];
    rate_params.Imax_pitch = rate_params.Imax_roll;
    rate_params.Imax_yaw = Imax_rate[1];

    // Stabilize mode parameters
    stab_params.RollP = SrollPID[0];
    stab_params.RollI = SrollPID[1];
    stab_params.RollD = SrollPID[2];
    stab_params.PitchP = SpitchPID[0];
    stab_params.PitchI = SpitchPID[1];
    stab_params.PitchD = SpitchPID[2];
    stab_params.YawP = SyawPID[0];
    stab_params.YawI = SyawPID[1];
    stab_params.YawD = SyawPID[2];
    stab_params.Imax_roll = Imax_stab[0];
    stab_params.Imax_pitch = stab_params.Imax_roll;
    stab_params.Imax_yaw = Imax_stab[1];
}

PID_out_t PID_rate(attitude_t des_rate, attitude_t actual_rate, float DT) {  // Actual rate will be in deg/s

    // Calculate error
    rate_out.error = des_rate - actual_rate;  // Probably the best for the Proportional term?

    if (abs(rate_out.error.roll) < PID_THRSHOLD) {
        rate_out.error.roll = 0.0;
    };
    if (abs(rate_out.error.pitch) < PID_THRSHOLD) {
        rate_out.error.pitch = 0.0;
    };
    if (abs(rate_out.error.yaw) < PID_THRSHOLD) {
        rate_out.error.yaw = 0.0;
    };

    // Calculate P term:
    rate_out.P_term.roll = rate_params.RollP * rate_out.error.roll;
    rate_out.P_term.pitch = rate_params.PitchP * rate_out.error.pitch;
    rate_out.P_term.yaw = rate_params.YawP * rate_out.error.yaw;

    // Calculate I term:
    rate_out.I_term.roll = rate_out.prev_Iterm.roll + (rate_params.RollI / 2) * (rate_out.error.roll + rate_out.prev_err.roll) * DT;
    rate_out.I_term.pitch = rate_out.prev_Iterm.pitch + (rate_params.PitchI / 2) * (rate_out.error.pitch + rate_out.prev_err.pitch) * DT;
    rate_out.I_term.yaw = rate_out.prev_Iterm.yaw + (rate_params.YawI / 2) * (rate_out.error.yaw + rate_out.prev_err.yaw) * DT;

    // Calculate D term: Explicitly calculating via numerical differentiation
    rate_out.D_term.roll = rate_params.RollD * (rate_out.error.roll - rate_out.prev_err.roll) / DT;
    rate_out.D_term.pitch = rate_params.PitchD * (rate_out.error.pitch - rate_out.prev_err.pitch) / DT;
    rate_out.D_term.yaw = rate_params.YawD * (rate_out.error.yaw - rate_out.prev_err.yaw) / DT;

    // Cap the I term
    rate_out.I_term.roll = constrain(rate_out.I_term.roll, -rate_params.Imax_roll, rate_params.Imax_roll);
    rate_out.I_term.pitch = constrain(rate_out.I_term.pitch, -rate_params.Imax_pitch, rate_params.Imax_pitch);
    rate_out.I_term.yaw = constrain(rate_out.I_term.yaw, -rate_params.Imax_yaw, rate_params.Imax_yaw);

    // Time propagation for relevant variables:
    rate_out.prev_err = rate_out.error;
    rate_out.prev_Iterm = rate_out.I_term;

    // Return the output
    rate_out.PID_ret = rate_out.P_term + rate_out.I_term + rate_out.D_term;
    return rate_out;  // This is the motor input values
}

// PID controller for stabilization
PID_out_t PID_stab(attitude_t des_angle, attitude_t angle, float DT) {
    // Calculate error
    stab_out.error = des_angle - angle;

    if (abs(stab_out.error.roll) < PID_THRSHOLD) {
        stab_out.error.roll = 0.0;
    };
    if (abs(stab_out.error.pitch) < PID_THRSHOLD) {
        stab_out.error.pitch = 0.0;
    };
    if (abs(stab_out.error.yaw) < PID_THRSHOLD) {
        stab_out.error.yaw = 0.0;
    };

    // Calculate P term:
    stab_out.P_term.roll = stab_params.RollP * stab_out.error.roll;
    stab_out.P_term.pitch = stab_params.PitchP * stab_out.error.pitch;
    stab_out.P_term.yaw = stab_params.YawP * stab_out.error.yaw;

    // Calculate I term:
    stab_out.I_term.roll = stab_out.prev_Iterm.roll + (stab_params.RollI / 2) * (stab_out.error.roll + stab_out.prev_err.roll) * DT;
    stab_out.I_term.pitch = stab_out.prev_Iterm.pitch + (stab_params.PitchI / 2) * (stab_out.error.pitch + stab_out.prev_err.pitch) * DT;
    stab_out.I_term.yaw = stab_out.prev_Iterm.yaw + (stab_params.YawI / 2) * (stab_out.error.yaw + stab_out.prev_err.yaw) * DT;

    // Calculate D term:
    stab_out.D_term.roll = stab_params.RollD * (stab_out.error.roll - stab_out.prev_err.roll) / DT;
    stab_out.D_term.pitch = stab_params.PitchD * (stab_out.error.pitch - stab_out.prev_err.pitch) / DT;
    stab_out.D_term.yaw = stab_params.YawD * (stab_out.error.yaw - stab_out.prev_err.yaw) / DT;

    // Cap the I term
    stab_out.I_term.roll = constrain(stab_out.I_term.roll, -stab_params.Imax_roll, stab_params.Imax_roll);
    stab_out.I_term.pitch = constrain(stab_out.I_term.pitch, -stab_params.Imax_pitch, stab_params.Imax_pitch);
    stab_out.I_term.yaw = constrain(stab_out.I_term.yaw, -stab_params.Imax_yaw, stab_params.Imax_yaw);

    // Time propagation for relevant variables:
    stab_out.prev_err = stab_out.error;
    stab_out.prev_Iterm = stab_out.I_term;

    // Return the output
    stab_out.PID_ret = (stab_out.P_term + stab_out.I_term + stab_out.D_term) ;

    stab_out.PID_ret.roll *= STAB_MASTER_MULTI;
    stab_out.PID_ret.pitch *= STAB_MASTER_MULTI;



    return stab_out;  // This output is the desired rate. now we can use the PID_rate function to get the motor input values
}

void Reset_PID() {
    rate_out.prev_err = {0.0, 0.0, 0.0};
    rate_out.prev_Iterm = {0.0, 0.0, 0.0};
    stab_out.prev_err = {0.0, 0.0, 0.0};
    stab_out.prev_Iterm = {0.0, 0.0, 0.0};
    rate_out.error = {0.0, 0.0, 0.0};
    stab_out.error = {0.0, 0.0, 0.0};

}