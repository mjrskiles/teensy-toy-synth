//
// Created by Michael Skiles on 9/22/21.
//

#include <synth_defines.h>
#include "io/InputPollster.h"


extern InputSnapshotBool INPUT_BUFFER_BOOL[];
extern InputSnapshotFloat INPUT_BUFFER_FLOAT[];
extern InputSnapshotUint8 INPUT_BUFFER_UINT8[];
extern InputSnapshotInt16 INPUT_BUFFER_INT16[];

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