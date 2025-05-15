#ifndef SENDER_H
#define SENDER_H

#include <Arduino.h>
#include "RTCom/RTCom.h"
#include "gnd_class.h"
#include "roller.h"

#define ODOM_TYPE 'O'
#define TWIST_TYPE 'T'
#define LINEAR_VELO 'L'

class sender {
   private:
    static RTComSession* socketSession;
    static gnd_bot* my_bot;
    static roller* my_roller;


   public:
    explicit sender(RTComSession* session, gnd_bot* gnd_instance, roller* roller_instance);
    static void update_session(RTComSession& newsession);
    void conver_and_send_data(float* data, size_t size,char type);
    void convert_data();
};

#endif