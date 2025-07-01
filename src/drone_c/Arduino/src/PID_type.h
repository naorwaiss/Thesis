#ifndef PID_TYPE_H
#define PID_TYPE_H

#include <Arduino.h>
#include "Var_types.h"


void setPID_params(PID_const_t* pid_consts);
PID_out_t PID_rate(attitude_t des_rate, attitude_t actual_rate, float DT);
PID_out_t PID_stab(attitude_t des_angle, attitude_t angle, float DT);
void Reset_PID();

#endif