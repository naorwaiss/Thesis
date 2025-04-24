#include "magwick.h"

Magwick::Magwick(Measurement_t* meas_data, attitude_t* ati_data) {
    meas = meas_data;
    euiler = ati_data;
}

void Magwick::init_magwick() {
    filter.begin(sampleRate_Hz);
}

void Magwick::magwick_operation() {
    filter.updateIMU(meas->gyroRAD.x, meas->gyroRAD.y, meas->gyroRAD.z, meas->acc.x, meas->acc.y, meas->acc.z);
    euiler->roll = filter.getRollRadians() * rad2deg;
    euiler->pitch = filter.getPitchRadians() * rad2deg;
    euiler->yaw = filter.getYawRadians() * rad2deg;
}
