#include "magwick.h"


void Magwick::init_magwick() {
    filter.begin(sampleRate_Hz);
}


Magwick::Magwick(Measurement_t* meas_data, attitude_t* ati_data) {
    meas = meas_data;
    euiler = ati_data;
    init_magwick();
}


void Magwick::magwick_operation() {
    // filter.updateIMU(meas->gyroRAD.x, meas->gyroRAD.y, meas->gyroRAD.z, meas->acc.x, meas->acc.y, meas->acc.z);
    filter.updateIMU(meas->gyro_HPF.x, meas->gyro_HPF.y, meas->gyro_HPF.z, meas->acc_LPF.x, meas->acc_LPF.y, meas->acc_LPF.z);

    euiler->roll = filter.getRollRadians() * rad2deg;
    euiler->pitch = filter.getPitchRadians() * rad2deg * -1;
    euiler->yaw = filter.getYawRadians() * rad2deg;
}
