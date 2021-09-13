//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_CONTROLLER_H
#define SYNTH_CONTROLLER_H

#include "LinkedList.h"
#include <Arduino.h>

//extern int bitMasks0thru15[16];
typedef unsigned long pgmtime_t;
template <class T>
struct InputSnapshot {
    const char* name;
    pgmtime_t time;
    T data;
};

/*
 * A class for creating lightweight callbacks that can be attached to I/O state changes
 */
template <class T>
class InputListener {
public:
    InputListener(void (*callback)(InputSnapshot<T>), const char *name);

    void update(T data);
private:
    void (*callback)(InputSnapshot<T>);
    const char* _name;
};

template <class T>
class VirtualInput {
public:
    VirtualInput();

    void set(T data);
    T get();
    void addListener(InputListener<T> listener);
protected:
    void notifyChangeListeners();
private:
    LinkedList<InputListener<T>> listeners;
    T state;
};

template <class T>
class InputPollster {
public:
    InputPollster(T (*pollCallback)(), void (*initCallback)());

    T poll();
    void init();
    void addInput(VirtualInput<T>);
private:
    LinkedList<VirtualInput<T>> virtualInputs;
    T _stateBuffer;
    T (*_pollCallback)();
    void (*_initCallback)();
};

template <class T>
class InputComponent {
public:
private:
    LinkedList<InputComponent> componentList;
    InputPollster<T> pollster;
};

// The controller gets raw input from the various peripherals
// and communicates input to the synthesizer
class InputController {
public:

};



template<class T>
void InputListener<T>::update(T data) {
    callback(InputSnapshot<T>(
            _name,
            millis(),
            data
            ));
}

template<class T>
InputListener<T>::InputListener(void (*callback)(InputSnapshot<T>), const char *name):callback(callback), _name(name) {}

template<class T>
VirtualInput<T>::VirtualInput() {
    listeners = LinkedList<T>();

}

template<class T>
void VirtualInput<T>::set(T data) {
    state = data;
    notifyChangeListeners();
}

template<class T>
T VirtualInput<T>::get() {
    return state;
}

template<class T>
void VirtualInput<T>::addListener(InputListener<T> listener) {
    listeners.Append(listener);
}

template<class T>
void VirtualInput<T>::notifyChangeListeners() {
    InputListener<T> listener = listeners.First();
    do {
        listener.update(state);
    } while ((listener = listeners.next()));
}

template<class T>
InputPollster<T>::InputPollster(T (*pollCallback)(), void (*initCallback)()):_pollCallback(pollCallback),
                                                                             _initCallback(initCallback) {}


template<class T>
void InputPollster<T>::init() {
    _initCallback();
}

template<class T>
T InputPollster<T>::poll() {
    return _pollCallback();
}

template<class T>
void InputPollster<T>::addInput (VirtualInput<T> virtualInput) {
    virtualInputs.Append(virtualInput);
}


#endif //SYNTH_CONTROLLER_H

