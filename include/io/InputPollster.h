//
// Created by Michael Skiles on 9/22/21.
//

#ifndef SYNTH_INPUTPOLLSTER_H
#define SYNTH_INPUTPOLLSTER_H

#include "VirtualInput.h"

class InputPollster {
public:
    InputPollster(void (*pollCallback)(VirtualInput *inputs, uint8_t size), void (*initCallback)(), VirtualInput *inputsArray, uint8_t size);

    void poll();
    void init();
private:
    VirtualInput *_virtualInputs;
    uint8_t _size = 0;
    void (*_pollCallback)(VirtualInput *inputs, uint8_t size); // the poll _callback has to put the dataa in the topBuffer
    void (*_initCallback)();
};

#endif //SYNTH_INPUTPOLLSTER_H
