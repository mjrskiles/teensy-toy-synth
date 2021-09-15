//
// Created by Michael Skiles on 9/11/21.
//

// #include "Controller.h"
// #include "LinkedList.h"
// #include "Arduino.h"

// template<class T>
// void InputListener<T>::update(T data) {
//     callback(InputSnapshot<T>(
//             _name,
//             millis(),
//             data
//     ));
// }

// template<class T>
// InputListener<T>::InputListener(void (*callback)(InputSnapshot<T>), const char *name):callback(callback), _name(name) {}

// template<class T>
// VirtualInput<T>::VirtualInput() {
//     listeners = LinkedList<T>();

// }

// template<class T>
// void VirtualInput<T>::set(T data) {
//     state = data;
//     notifyChangeListeners();
// }

// template<class T>
// T VirtualInput<T>::get() {
//     return state;
// }

// template<class T>
// void VirtualInput<T>::addListener(InputListener<T> listener) {
//     listeners.Append(listener);
// }

// template<class T>
// void VirtualInput<T>::notifyChangeListeners() {
//     InputListener<T> listener = listeners.First();
//     do {
//         listener.update(state);
//     } while ((listener = listeners.next()));
// }

// template<class T>
// InputPollster<T>::InputPollster(T (*pollCallback)(), void (*initCallback)()):_pollCallback(pollCallback),
//                                                                              _initCallback(initCallback) {}


// template<class T>
// void InputPollster<T>::init() {
//     _initCallback();
// }

// template<class T>
// T InputPollster<T>::poll() {
//     return _pollCallback();
// }

// template<class T>
// void InputPollster<T>::addInput(VirtualInput<T> virtualInput) {
//     virtualInputs.Append(virtualInput);
// }


// // specialization impl
// template<>
// void VirtualInput<VirtualButtonState>::addListener(InputListener<VirtualButtonState> listener) {
//     listeners.Append(listener);
// }

// template<>
// VirtualInput<VirtualButtonState>::VirtualInput() : state(false) {}

// template<>
// InputListener<VirtualButtonState>::InputListener(void (*cb)(InputSnapshot<VirtualButtonState>), char const *name)
//         : callback(cb), _name(name) {}

// VirtualButtonState pollcb() {
//     VirtualButtonState state = VirtualButtonState((bool)false);
//     return state;
// }
// VirtualButtonState (*testpollcb)() = &pollcb;

// template<>
// InputPollster<VirtualButtonState>::InputPollster(VirtualButtonState (*pollCallback)(), void (*initCallback)()) : _pollCallback(pollCallback), _initCallback(initCallback) {
//     _stateBuffer = VirtualButtonState(false);
// }
