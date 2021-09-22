//
// Created by Michael Skiles on 9/22/21.
//

#include "io/InputListener.h"

// get the inputs out of th buffers instead of using void pointers
void InputListener::update(int index, InputDataType inputDataType) {
    InputSnapshot *snapshot;
    switch (inputDataType) {
        case BOOL:
            snapshot = &INPUT_BUFFER_BOOL[index];
            break;
            case FLOAT:
                snapshot = &INPUT_BUFFER_FLOAT[index];
                break;
                case UINT8:
                    snapshot = &INPUT_BUFFER_UINT8[index];
                    break;
                    case INT16:
                        snapshot = &INPUT_BUFFER_INT16[index];
                        break;
    }
    _callback(snapshot);
}


InputListener::InputListener(void (*callback)(InputSnapshot *), const char *name) {
    _callback = callback;
    _name = name;
}