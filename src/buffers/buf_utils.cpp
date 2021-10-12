//
// Created by Michael Skiles on 10/1/21.
//

#include "buffers/buf_utils.h"


bool isAnyKeyboardKeyPressed() {
    for(int i = 0; i < 16; i++) {
        if (INPUT_BUFFER_BOOL[i].asBool()) return true;
    }
    return false;
}

uint16_t whichBitsAreNewlyOn(uint16_t oldWord, uint16_t newWord) {
    uint16_t changed = oldWord ^ newWord;
    return changed & newWord;
}

uint16_t whichBitsAreNewlyOff(uint16_t oldWord, uint16_t newWord) {
    uint16_t changed = oldWord ^ newWord;
    return changed & ~newWord;
}

/*
 *

 */