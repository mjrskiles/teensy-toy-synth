//
// Created by Michael Skiles on 9/22/21.
//

#include "io/InputPollster.h"

void InputPollster::init() {
    _initCallback();
}

void* InputPollster::poll() {
    return _pollCallback();
}

void InputPollster::addInput(VirtualInput virtualInput) {
    if (_currentSize < MAX_INPUTS_PER_POLLSTER) _virtualInputs[_currentSize++] = virtualInput;
}

InputPollster::InputPollster(void *(*pollCallback)(), void (*initCallback)(), VirtualInput *inputsArray) {
    _pollCallback = pollCallback;
    _initCallback = initCallback;
    _virtualInputs = inputsArray;
}