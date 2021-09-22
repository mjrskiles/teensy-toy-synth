//
// Created by Michael Skiles on 9/22/21.
//

#include "io/InputListener.h"

extern InputSnapshotBool INPUT_BUFFER_BOOL[];
extern InputSnapshotFloat INPUT_BUFFER_FLOAT[];
extern InputSnapshotUint8 INPUT_BUFFER_UINT8[];
extern InputSnapshotInt16 INPUT_BUFFER_INT16[];

// get the inputs out of th buffers instead of using void pointers
void InputListener::update(int index, InputDataType inputDataType) {
    switch (inputDataType) {
        case BOOL:
             _callback(INPUT_BUFFER_BOOL[index]);
            break;
        case FLOAT:
            _callback(INPUT_BUFFER_FLOAT[index]);
            break;
        case UINT8:
            _callback(INPUT_BUFFER_UINT8[index]);
            break;
        case INT16:
            _callback(INPUT_BUFFER_INT16[index]);
            break;
        default:
            Serial.println("Input listener update terminated without executing a callback.");
    }
}


InputListener::InputListener(void (*callback)(InputSnapshot&), const char *name) {
    _callback = callback;
    _name = name;
}