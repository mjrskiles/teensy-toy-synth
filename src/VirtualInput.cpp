//
// Created by Michael Skiles on 9/22/21.
//

#include "io/VirtualInput.h"
#include "io/InputListener.h"

void VirtualInput::addListener(InputListener listener) {
    if (_currentSize > MAX_LISTENERS_PER_INPUT) _inputListeners[_currentSize++] = listener;
}

void VirtualInput::notifyChangeListeners() {
    for (uint8_t i = 0; i < _currentSize; i++) {
        _inputListeners[i].update(_index, _inputDataType);
    }
}

VirtualInput::VirtualInput(InputListener *listeners) {
    _inputListeners = listeners;
}

VirtualInput::VirtualInput(InputListener *inputListeners, uint8_t currentSize, int index, InputDataType inputDataType)
: _inputListeners(inputListeners), _currentSize(currentSize), _index(index), _inputDataType(inputDataType) {}