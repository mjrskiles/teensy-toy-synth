//
// Created by Michael Skiles on 10/1/21.
//

#include "model/buffers/buf_utils.h"


bool isAnyKeyboardKeyPressed() {
    for(int i = 0; i < 16; i++) {
        if (INPUT_BUFFER_BOOL[i].asBool()) return true;
    }
    return false;
}
