#ifndef SENDER_H
#define SENDER_H

#include <Arduino.h>
#include "RTCom/RTCom.h"
#include "gnd_class.h"
#include "roller.h"
#include "ImuMadgwick.h"


#define ODOM_TYPE 'O'
#define TWIST_TYPE 'T'
#define LINEAR_VELO 'L'
#define ROLLER_DATA_TYPE 'r'
#define IMU_TYPE 'I'


class sender {
   private: 
    static gnd_bot* _my_bot;
    static roller* _my_roller;
    static RTComSession* _socketSession;


   public:
    explicit sender(gnd_bot* gnd_instance, roller* roller_instance);
    void update_session(RTComSession* newsession);
    void convert_data();
    void send_data(float *data, uint8_t type);
};

#endif