//
// Created by Michael Skiles on 9/22/21.
//

#include <cstdint>
#include "io/input_pollster.h"


void InputPollster::init() {
    _initCallback();
}

void InputPollster::poll() {
    _pollCallback();
}


InputPollster::InputPollster(void (*pollCallback)(), void (*initCallback)(), uint8_t size) {
    _pollCallback = pollCallback;
    _initCallback = initCallback;
}