#ifndef MAGWICK_H
#define MAGWICK_H

#include "Var_types.h"
#include <MadgwickAHRS.h>



class Magwick {
   private:
   Measurement_t* Magwick::meas = nullptr;
   attitude_t* Magwick::euiler = nullptr;
   float sampleRate_Hz = 100.0f;  // IMU data rate
   Madgwick filter;

   /* data */
   public:
   explicit Magwick(Measurement_t* meas_data,attitude_t* ati_data);
   void init_magwick();
   void magwick_operation();

};

#endif