#include "swing_drone/simple_rate_mode.hpp"


simple_rate_mode::simple_rate_mode(pub* pub_ptr, imu_data* imu_read, joy_data* joy_read , float DT_hz)
{
    _imu_read = imu_read;
    _joy_read = joy_read;
    _DT_SEC = 1.0f / DT_hz;
    _pub_ptr = pub_ptr;
}



void simple_rate_mode::angle_constrain() { 
    _des_rate.roll = map_range(_joy_read->roll, -1.0f, 1.0f, -_rate_angle_limit, _rate_angle_limit);
    _des_rate.pitch = map_range(_joy_read->pitch, -1.0f, 1.0f, -_rate_angle_limit, _rate_angle_limit);
    _des_rate.yaw = map_range(_joy_read->yaw, -1.0f, 1.0f, -_rate_angle_limit, _rate_angle_limit);
    _pub_ptr->publish_dis_rate(_des_rate);
    _pub_ptr->publish_actual_rate(_actual_rate);
    _throttle_modifier = map_range(_joy_read->thrust, -1.0f, 1.0f, MIN_PWM, MAX_PWM);
}

void simple_rate_mode::PID_operation() {  // Actual rate will be in deg/s

    // Calculate error
    PID_rate.error = _des_rate - _actual_rate;  // Probably the best for the Proportional term?

    // Calculate P term:
    PID_rate.P_term.roll = _pid_const.rate_roll[0] * PID_rate.error.roll;
    PID_rate.P_term.pitch = _pid_const.rate_pitch[0] * PID_rate.error.pitch;
    PID_rate.P_term.yaw = _pid_const.rate_yaw[0] * PID_rate.error.yaw;

    // Calculate I term:
    PID_rate.I_term.roll = PID_rate.prev_Iterm.roll + _pid_const.rate_roll[1] * ((PID_rate.error.roll + PID_rate.prev_err.roll)/2) * _DT_SEC;
    PID_rate.I_term.pitch = PID_rate.prev_Iterm.pitch + _pid_const.rate_pitch[1] * ((PID_rate.error.pitch + PID_rate.prev_err.pitch)/2) * _DT_SEC;
    PID_rate.I_term.yaw = PID_rate.prev_Iterm.yaw + _pid_const.rate_yaw[1] * ((PID_rate.error.yaw + PID_rate.prev_err.yaw)/2) * _DT_SEC;

    PID_rate.I_term.roll = constrain(PID_rate.I_term.roll, -_pid_const.rate_roll[2], _pid_const.rate_roll[2]);
    PID_rate.I_term.pitch = constrain(PID_rate.I_term.pitch, -_pid_const.rate_pitch[2], _pid_const.rate_pitch[2]);
    PID_rate.I_term.yaw = constrain(PID_rate.I_term.yaw, -_pid_const.rate_yaw[2], _pid_const.rate_yaw[2]);

    //apply numeric derivative 
    PID_rate.D_term.roll = (PID_rate.error.roll - PID_rate.prev_err.roll) / _DT_SEC;
    PID_rate.D_term.pitch = (PID_rate.error.pitch - PID_rate.prev_err.pitch) / _DT_SEC;
    PID_rate.D_term.yaw = (PID_rate.error.yaw - PID_rate.prev_err.yaw) / _DT_SEC;

    PID_rate.prev_err = PID_rate.error;
    PID_rate.prev_Iterm = PID_rate.I_term;
    // Return the output
    PID_rate.PID_return = PID_rate.P_term + PID_rate.I_term + PID_rate.D_term;
    _pub_ptr->pid_value_publish(PID_rate);
}


void simple_rate_mode::Motor_Mix() {
    _Motor_struct.motor_A = _throttle_modifier + PID_rate.PID_return.pitch - PID_rate.PID_return.roll + PID_rate.PID_return.yaw;
    _Motor_struct.motor_B = _throttle_modifier + PID_rate.PID_return.pitch - PID_rate.PID_return.roll - PID_rate.PID_return.yaw;
    _Motor_struct.motor_C = _throttle_modifier + PID_rate.PID_return.pitch + PID_rate.PID_return.roll + PID_rate.PID_return.yaw;
    _Motor_struct.motor_D = _throttle_modifier + PID_rate.PID_return.pitch + PID_rate.PID_return.roll - PID_rate.PID_return.yaw;
    _Motor_struct.motor_E = _throttle_modifier - PID_rate.PID_return.pitch + PID_rate.PID_return.roll + PID_rate.PID_return.yaw;
    _Motor_struct.motor_F = _throttle_modifier - PID_rate.PID_return.pitch + PID_rate.PID_return.roll - PID_rate.PID_return.yaw;
    _Motor_struct.motor_G = _throttle_modifier - PID_rate.PID_return.pitch - PID_rate.PID_return.roll + PID_rate.PID_return.yaw;
    _Motor_struct.motor_H = _throttle_modifier - PID_rate.PID_return.pitch - PID_rate.PID_return.roll - PID_rate.PID_return.yaw;
    
    // // Constrain the values to be between 0 and 1000
    _Motor_struct.motor_A = constrain(_Motor_struct.motor_A, MIN_PWM, MAX_PWM);
    _Motor_struct.motor_B = constrain(_Motor_struct.motor_B, MIN_PWM, MAX_PWM);
    _Motor_struct.motor_C = constrain(_Motor_struct.motor_C, MIN_PWM, MAX_PWM);
    _Motor_struct.motor_D = constrain(_Motor_struct.motor_D, MIN_PWM, MAX_PWM);
    _Motor_struct.motor_E = constrain(_Motor_struct.motor_E, MIN_PWM, MAX_PWM);
    _Motor_struct.motor_F = constrain(_Motor_struct.motor_F, MIN_PWM, MAX_PWM);
    _Motor_struct.motor_G = constrain(_Motor_struct.motor_G, MIN_PWM, MAX_PWM);
    _Motor_struct.motor_H = constrain(_Motor_struct.motor_H, MIN_PWM, MAX_PWM);
    _pub_ptr->publish_motor_data(_Motor_struct);


}


void simple_rate_mode::run_rate_mode() {
    _pub_ptr->publish_swings(false);
    angle_constrain();
    PID_operation();
    Motor_Mix();
}






/*

עקרונות השקלול – למה לפעמים + ולפעמים -?
במיקסר של מנועים (motor mixer), אתה בעצם שואל:

"איך כל מנוע תורם לתנועה מסוימת (Roll, Pitch, Yaw)?"

כדי לענות על זה, נבין כל אחד מהצירים:

🎚️ 1. Roll (גלגול – שמאלה/ימינה)
המערכת מנסה להטות את הרחפן שמאלה או ימינה סביב הציר הקדמי-אחורי.

אם נרצה להתגלגל ימינה, המנועים בצד ימין צריכים למשוך פחות, והמנועים בצד שמאל צריכים למשוך יותר.

לכן:

מנועים בצד שמאל ➝ +Roll

מנועים בצד ימין ➝ -Roll

🎚️ 2. Pitch (הטיה קדימה/אחורה)
המערכת מנסה להטות את הרחפן קדימה או אחורה סביב הציר הצדדי.

אם נרצה להטות קדימה, המנועים בקדימה צריכים למשוך פחות, והמנועים מאחור צריכים למשוך יותר.

לכן:

מנועים באחור ➝ +Pitch

מנועים בקדימה ➝ -Pitch

🎚️ 3. Yaw (סיבוב סביב ציר אנכי)
Yaw הוא מיוחד: הוא לא תלוי במיקום, אלא בכיוון הסיבוב של כל מנוע.

מנוע שמסתובב עם כיוון השעון (CW) מייצר ריאקציית סיבוב נגד כיוון השעון.

מנוע שמסתובב נגד כיוון השעון (CCW) מייצר ריאקציה עם כיוון השעון.

אז:

מנועים CCW ➝ +Yaw

מנועים CW ➝ -Yaw

✈️ דוגמה עם מנוע 1:
נניח מנוע 1 נמצא בקדמת הרחפן בצד שמאל, ומסתובב נגד כיוון השעון (CCW):

מיקום שמאלי ➝ +Roll

מיקום קדמי ➝ -Pitch

סיבוב CCW ➝ +Yaw

ולכן:

cpp
Copy
Edit
motor1 = throttle - roll - pitch + yaw;
(שים לב ש־roll כאן הוא עם סימן שלילי, כי אתה מחסר אותו כדי לקבל יותר thrust בצד שמאל)

🧠 כלל אצבע:
מיקום/סיבוב	ערך ל־Mix
בצד שמאל	+Roll
בצד ימין	-Roll
בקדימה	-Pitch
באחורה	+Pitch
מנוע CCW	+Yaw
מנוע CW	
*/