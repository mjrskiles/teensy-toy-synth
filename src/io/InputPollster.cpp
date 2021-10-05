//
// Created by Michael Skiles on 9/22/21.
//

#include "io/InputPollster.h"


extern InputSnapshotBool INPUT_BUFFER_BOOL[];
extern InputSnapshotFloat INPUT_BUFFER_FLOAT[];
extern InputSnapshotUint8 INPUT_BUFFER_UINT8[];
extern InputSnapshotInt16 INPUT_BUFFER_INT16[];

void InputPollster::init() {
    _initCallback();
}

void InputPollster::poll() {
    _pollCallback();
}


InputPollster::InputPollster(void (*pollCallback)(), void (*initCallback)(), uint8_t size) {
    _pollCallback = pollCallback;
    _initCallback = initCallback;
}