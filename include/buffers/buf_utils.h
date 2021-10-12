//
// Created by Michael Skiles on 10/1/21.
//

#ifndef TEENSY_SYNTH_BUF_UTILS_H
#define TEENSY_SYNTH_BUF_UTILS_H

#include "buffers/buffers.h"

bool isAnyKeyboardKeyPressed();

uint16_t whichBitsAreNewlyOn(uint16_t oldWord, uint16_t newWord);
uint16_t whichBitsAreNewlyOff(uint16_t oldWord, uint16_t newWord);

#endif //TEENSY_SYNTH_BUF_UTILS_H
