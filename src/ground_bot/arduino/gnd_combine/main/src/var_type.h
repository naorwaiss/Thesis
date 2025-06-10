#ifndef VARTYPE_H
#define VARTYPE_H

struct vec3 {
    float x;
    float y;
    float z;
};

typedef struct
{
    float q0;
    float q1;
    float q2;
    float q3;
} quaternion_t;

typedef struct
{
    float roll;
    float pitch;
    float yaw;
} atitude_t;

struct imu_data {
    vec3 accel;
    vec3 gyro;
    quaternion_t quaternion;
    atitude_t atitude;
};

struct ALFA_BETA_FILTER {
    /* data */
    double _dt_sec;
    float _a,_b;
    float _xk,_xk_1,_vk,_vk_1,_rk;


    float vk;

    ALFA_BETA_FILTER(double dt_sec,float a ,float b) {
        _dt_sec = dt_sec;
        _a = a;
        _b = b;
    }

    void alfa_beta_calc(float raw_data) {
        double _xm = (raw_data * 2.0 * M_PI) / this->_dt_sec;
        _xk = _xk_1+(vk*_dt_sec);
        _vk = _vk_1;
        _rk = _xm-_xk;
        _xk += _a*_rk;
        _vk += _b*_rk/_dt_sec;
        _xk_1 = _xk;
        _vk_1 = _vk;
        //velocity is vk_1
        //position is xk_1 - after the calc
    }
};

struct odometry {
    vec3 velocity;
    vec3 position;
};

#endif
