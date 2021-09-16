//
// Created by Michael Skiles on 9/11/21.
//

// #include "Controller.h"
// #include "LinkedList.h"

#include "Controller.h"

InputSnapshot::InputSnapshot(const char *name, unsigned long time, void *data) : _name(name), _time(time),
                                                                                 _data(data) {}

                                                                                 void InputListener::update(void *data) {
    InputSnapshot snapshot = InputSnapshot(
            _name,
            millis(),
            data
            );
    callback(snapshot);
}


InputListener::InputListener(void (*callback)(InputSnapshot), const char *name):callback(callback), _name(name) {}

void VirtualInput::set(void *data) {
    state = data;
    notifyChangeListeners();
}

void* VirtualInput::get() {
    return state;
}

void VirtualInput::addListener(InputListener listener) {
    if (_currentSize > MAX_LISTENERS_PER_INPUT) _inputListeners[_currentSize++] = listener;
}

void VirtualInput::notifyChangeListeners() {
    for (uint8_t i = 0; i < _currentSize; i++) {
        _inputListeners[i].update(state);
    }
}

VirtualInput::VirtualInput(InputListener *listeners) {
    _inputListeners = listeners;
}

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

uint8_t InputController::update() {
    uint8_t numRead = 0;
    for(uint8_t i = 0; i < MAX_POLLSTERS; i++) {
        // poll all the pollsters
    }
    return numRead;
}

InputController::InputController(const InputPollster &pollster) : _pollster(pollster) {}
