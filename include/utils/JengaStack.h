//
// Created by mjrsk on 10/3/2021.
//

#ifndef TEENSY_SYNTH_JENGASTACK_H
#define TEENSY_SYNTH_JENGASTACK_H

#include "cstdint"
#include <usb_serial.h>
#define JENGA_STACK_SIZE_MAX 16
/*
 * A Jenga stack can have arbitrary members removed while staying intact
 */
class JengaStack {
public:
    void push(uint8_t elem);
    uint8_t pop();
    uint8_t removeAtIndex(uint8_t index);
    uint8_t getElemAtIndex(uint8_t index);
    uint8_t size();
private:
    uint8_t _stack[JENGA_STACK_SIZE_MAX];  // Who could possibly press more than 16 keys???
    uint8_t _size = 0;
};

#endif //TEENSY_SYNTH_JENGASTACK_H
