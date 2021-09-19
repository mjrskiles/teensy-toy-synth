//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_CONTROLLER_H
#define SYNTH_CONTROLLER_H

#include "LinkedList.h"
#include "Arduino.h"

#define MAX_LISTENERS_PER_INPUT (uint8_t)4
#define MAX_INPUTS_PER_POLLSTER (uint8_t)8
#define MAX_POLLSTERS (uint8_t)24

//extern int bitMasks0thru15[16];
typedef unsigned long pgmtime_t;

enum InputDataType : uint8_t {
    BOOL,
    CONTINUOUS_INTEGER,
    CONTINUOUS_FLOAT
};

struct InputSnapshot {
    InputSnapshot(const char *name, pgmtime_t time, void *data);

    const char* name;
    pgmtime_t time;
    void *data;
    InputDataType dataType = BOOL;
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
    explicit VirtualInput(InputListener *listenersArray);

    void set(void *data);
    void* get();
    void addListener(InputListener listener);
protected:
    void notifyChangeListeners();
private:
    InputListener *_inputListeners;
    uint8_t _currentSize = 0;
    void *state = nullptr;
};

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
    void *(*_pollCallback)();
    void (*_initCallback)();
};

// The controller gets raw input from the various peripherals
// and communicates input to the synthesizer
class InputController {
public:
    InputController(const InputPollster &pollster);

    uint8_t update(); // Returns the number of individual VirtualInputs read

private:
    InputPollster _pollster;
};

class VirtualButtonState {
public:
    explicit VirtualButtonState(bool state) : _state(state) {}

    bool state() { return _state; }
private:
    bool _state;
};


#endif //SYNTH_CONTROLLER_H

