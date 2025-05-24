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
#define ROLLER_DATA_TYPE 'R'
#define IMU_TYPE 'I'


class sender {
   private:
    static RTComSession* socketSession;
    static gnd_bot* my_bot;
    static roller* my_roller;
    static ImuMadgwick* my_imu;


   public:
    explicit sender(RTComSession* session, gnd_bot* gnd_instance, roller* roller_instance,ImuMadgwick* imu_instance);
    static void update_session(RTComSession& newsession);
    void conver_and_send_data(float* data, size_t size,char type);
    void convert_data();
};

#endif