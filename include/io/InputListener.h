//
// Created by Michael Skiles on 9/22/21.
//

#ifndef SYNTH_INPUTLISTENER_H
#define SYNTH_INPUTLISTENER_H

#include "Globals.h"
/*
 * A class for creating lightweight callbacks that can be attached to I/O state changes
 * This is the observer
 */
class InputListener {
public:
    InputListener(void (*callback)(InputSnapshot*), const char *name);

    void update(int index, InputDataType inputDataType);
private:
    void (*_callback)(InputSnapshot*){};
    const char* _name{};
};

#endif //SYNTH_INPUTLISTENER_H
