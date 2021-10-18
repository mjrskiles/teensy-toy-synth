//
// Created by Michael Skiles on 10/1/21.
//

#include "buffers/buf_utils.h"

const uint16_t logical_loc_to_mask[] = {
        0b0000000000000001,
        0b0000000000000010,
        0b0000000000000100,
        0b0000000000001000,
        0b0000000000010000,
        0b0000000000100000,
        0b0000000001000000,
        0b0000000010000000,
        0b0000000100000000,
        0b0000001000000000,
        0b0000010000000000,
        0b0000100000000000,
        0b0001000000000000,
        0b0010000000000000,
        0b0100000000000000,
        0b1000000000000000
};


bool isOneAtIndex(uint16_t word, int index) {
    uint16_t mask = logical_loc_to_mask[index];
    return word & mask;
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