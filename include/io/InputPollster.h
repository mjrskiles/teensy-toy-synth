//
// Created by Michael Skiles on 9/22/21.
//

#ifndef SYNTH_INPUTPOLLSTER_H
#define SYNTH_INPUTPOLLSTER_H

#include "VirtualInput.h"

class InputPollster {
public:
    InputPollster(void (*pollCallback)(), void (*initCallback)(), uint8_t size);

    void poll();
    void init();
private:
    void (*_pollCallback)(); // the poll _callback has to put the dataa in the buffer
    void (*_initCallback)();
};

#endif //SYNTH_INPUTPOLLSTER_H
