#ifndef MAGWICK_H
#define MAGWICK_H

#include "Var_types.h"
#include <MadgwickAHRS.h>



class Magwick {
   private:
   static Measurement_t* meas;
   static attitude_t* euiler;
   float sampleRate_Hz = 100.0f;  // IMU data rate

   /* data */
   public:
   Madgwick filter;
   explicit Magwick(Measurement_t* meas_data,attitude_t* ati_data);
   void init_magwick();
   void magwick_operation();

};

#endif