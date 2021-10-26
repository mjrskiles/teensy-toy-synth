//
// Created by Michael Skiles on 10/1/21.
//

#ifndef TEENSY_SYNTH_BUF_UTILS_H
#define TEENSY_SYNTH_BUF_UTILS_H

#include <cstdint>

extern const uint16_t logical_loc_to_mask[16];

bool isAnyKeyboardKeyPressed();
bool isOneAtIndex(uint16_t word, int index);
uint16_t whichBitsAreNewlyOn(uint16_t oldWord, uint16_t newWord);
uint16_t whichBitsAreNewlyOff(uint16_t oldWord, uint16_t newWord);

#endif //TEENSY_SYNTH_BUF_UTILS_H
