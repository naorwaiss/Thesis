#ifndef STD_OPERATION_HPP
#define STD_OPERATION_HPP

#include "Var_type.hpp"
#include "swing_drone/pub.hpp"


class std_operation{
    public:
        std_operation(joy_data* joy_read );
        drone_mod mode_switch();
        bool arm_state();
        arm_statuse arm_info;
        

    private:
        joy_data* _joy_read;
};

#endif