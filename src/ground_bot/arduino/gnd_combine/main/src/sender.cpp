#include "sender.h"

gnd_bot* sender::_my_bot = nullptr;
roller* sender::_my_roller = nullptr;
RTComSession* sender::_socketSession = nullptr;

uint8_t roller_data_byte[sizeof(float) * 4];


sender::sender(gnd_bot* gnd_instance, roller* roller_instance) {
    _my_bot = gnd_instance;      
    _my_roller = roller_instance;

}

void sender::update_session(RTComSession* newsession) {
    _socketSession = newsession;
}

void sender::convert_data() {
    float roller_data[4] = {_my_roller->load_cell.tension,_my_roller->load_cell.dis_tension ,_my_roller->load_cell.error, _my_roller->pid.sum_error};
    send_data(roller_data, ROLLER_DATA_TYPE);

}

void sender::send_data(float *data, uint8_t type) {
    uint8_t data_byte[sizeof(data)*sizeof(float)];
    memcpy(data_byte, &data, sizeof(data_byte));
    _socketSession->emitTyped(data_byte, sizeof(data_byte), type);
}
