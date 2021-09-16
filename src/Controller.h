//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_CONTROLLER_H
#define SYNTH_CONTROLLER_H

#include "../include/LinkedList.h"
#include "Arduino.h"

//extern int bitMasks0thru15[16];
typedef unsigned long pgmtime_t;
struct InputSnapshot {
    InputSnapshot(const char *name, pgmtime_t time, void *data);

    const char* _name;
    pgmtime_t _time;
    void *_data;
};

/*
 * A class for creating lightweight callbacks that can be attached to I/O state changes
 * This is the observer
 */
class InputListener {
public:
    InputListener(void (*callback)(InputSnapshot), const char *name);

    void update(void *data);
private:
    void (*callback)(InputSnapshot){};
    const char* _name{};
};

class VirtualInput {
public:
    VirtualInput();

    void set(void *data);
    void* get();
    void addListener(InputListener listener);
protected:
    void notifyChangeListeners();
private:
    LinkedList<InputListener> listeners;
    void *state;
};

class InputPollster {
public:
    InputPollster(void* (*pollCallback)(), void (*initCallback)());

    void* poll();
    void init();
    void addInput(VirtualInput);
private:
    LinkedList<VirtualInput> virtualInputs;
    void *_stateBuffer;
    void *(*_pollCallback)();
    void (*_initCallback)();
};

class InputComponent {
public:
private:
    LinkedList<InputComponent> componentList;
    InputPollster pollster;
};

// The controller gets raw input from the various peripherals
// and communicates input to the synthesizer
class InputController {
public:

};

class VirtualButtonState {
public:
    VirtualButtonState(bool state) : _state(state) {}

    bool state() { return _state; }
private:
    bool _state;
};


#endif //SYNTH_CONTROLLER_H

