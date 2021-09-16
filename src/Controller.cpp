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

VirtualInput::VirtualInput() {
    listeners = LinkedList<InputListener>();
}

void VirtualInput::set(void *data) {
    state = data;
    notifyChangeListeners();
}

void* VirtualInput::get() {
    return state;
}

void VirtualInput::addListener(InputListener listener) {
    listeners.Append(listener);
}

void VirtualInput::notifyChangeListeners() {
    InputListener listener = listeners.First();
    do {
        listener.update(state);
    } while ((listeners.next()));
}

InputPollster::InputPollster(void* (*pollCallback)(), void (*initCallback)()):_pollCallback(pollCallback),
_initCallback(initCallback) {}


void InputPollster::init() {
    _initCallback();
}

void* InputPollster::poll() {
    return _pollCallback();
}

void InputPollster::addInput(VirtualInput virtualInput) {
    virtualInputs.Append(virtualInput);
}
