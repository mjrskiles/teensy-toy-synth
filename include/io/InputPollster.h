//
// Created by Michael Skiles on 9/22/21.
//

#ifndef SYNTH_INPUTPOLLSTER_H
#define SYNTH_INPUTPOLLSTER_H

class InputPollster {
public:
    InputPollster(void* (*pollCallback)(), void (*initCallback)(), VirtualInput *inputsArray);

    void* poll();
    void init();
    void addInput(VirtualInput);
private:
    VirtualInput *_virtualInputs;
    uint8_t _currentSize = 0;
    void *_stateBuffer = nullptr;
    void *(*_pollCallback)(); // the poll _callback has to put the dataa in the buffer
    void (*_initCallback)();
};

#endif //SYNTH_INPUTPOLLSTER_H
