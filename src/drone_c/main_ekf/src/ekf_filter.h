#ifndef EKFFILTER_H
#define EKFFILTER_H


#include "Var_types.h"

class EKF {
public:
    EKF(Measurement_t* meas);


private:
    Measurement_t* measurement;

};

#endif
