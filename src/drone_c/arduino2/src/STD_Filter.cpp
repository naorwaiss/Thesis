#include "STD_Filter.h"

STD_Filter::STD_Filter(Measurement_t* meas_data, float sample_hz) {
    _dt = 1.0f / sample_hz;
    this->_meas_data = meas_data;
}

void STD_Filter::acc_low_pass_filter() {
    _meas_data->acc_LPF.y = ALPHA_ACC_LPF * _meas_data->acc.y + (1 - ALPHA_ACC_LPF) * _meas_data->acc_LPF.y;
    _meas_data->acc_LPF.x = ALPHA_ACC_LPF * _meas_data->acc.x + (1 - ALPHA_ACC_LPF) * _meas_data->acc_LPF.x;
    _meas_data->acc_LPF.z = ALPHA_ACC_LPF * _meas_data->acc.z + (1 - ALPHA_ACC_LPF) * _meas_data->acc_LPF.z;
}

void STD_Filter::gyro_low_pass_filter() {
    _meas_data->gyro_LPF.x = ALPHA_GYRO_LPF * _meas_data->gyroDEG.x + (1 - ALPHA_GYRO_LPF) * _meas_data->gyro_LPF.x;
    _meas_data->gyro_LPF.y = ALPHA_GYRO_LPF * _meas_data->gyroDEG.y + (1 - ALPHA_GYRO_LPF) * _meas_data->gyro_LPF.y;
    _meas_data->gyro_LPF.z = ALPHA_GYRO_LPF * _meas_data->gyroDEG.z + (1 - ALPHA_GYRO_LPF) * _meas_data->gyro_LPF.z;
}

void STD_Filter::gyro_high_pass_filter() {
    _meas_data->gyro_HPF.x = ALPHA_HPF * (_meas_data->gyro_HPF.x + _meas_data->gyroRAD.x - _gyroPrev.x);
    _meas_data->gyro_HPF.y = ALPHA_HPF * (_meas_data->gyro_HPF.y + _meas_data->gyroRAD.y - _gyroPrev.y);
    _meas_data->gyro_HPF.z = ALPHA_HPF * (_meas_data->gyro_HPF.z + _meas_data->gyroRAD.z - _gyroPrev.z);

    _gyroPrev.x = _meas_data->gyroRAD.x;
    _gyroPrev.y = _meas_data->gyroRAD.y;
    _gyroPrev.z = _meas_data->gyroRAD.z;
}

void STD_Filter::all_filter() {
    gyro_high_pass_filter();

}