//
// Created by mjrsk on 10/3/2021.
//


#include "utils/JengaStack.h"
#define JENGA_ERR 255

void JengaStack::push(uint8_t elem) {
    if (_size < JENGA_STACK_SIZE_MAX) {
        _stack[_size] = elem;
        _size++;
    } else {
        Serial.println("Jenga stack is full");
    }
}

uint8_t JengaStack::pop() {
    uint8_t val = JENGA_ERR;
    if (_size) {
        val = _stack[_size];
    }
    return val;
}
// TODO sometimes this function is leaving 1 voice active with no key presses I think
uint8_t JengaStack::removeAtIndex(uint8_t index) {
    Serial.printf("Removing from Jenga stack at index: %d\n", index);
    Serial.printf("Size was: %d\n", _size);
    if (index > _size || _size == 0) return JENGA_ERR;
    if (index == JENGA_STACK_SIZE_MAX) {
        _size--;
        Serial.printf("Now: %d\n", (int) _size);
        return _stack[_size + 1];
    }

    // if control has reached this point, the stack is between 1 and max -1 size
    uint8_t val = _stack[index];
    for (uint8_t i = index; i < _size; i++) {
        _stack[i] = _stack[i++];
    }
    _size--;
    Serial.printf("Now: %d\n", (int) _size);
    return val;
}

uint8_t JengaStack::removeByValue(uint8_t val) {
    uint8_t removed = JENGA_ERR;
    for (int i = 0; i < JENGA_STACK_SIZE_MAX; i++) {
        if (_stack[i] == val) {
            removed = removeAtIndex(i);
        }
    }
    return removed;
}

uint8_t JengaStack::getElemAtIndex(uint8_t index) {
    if (index < _size) {
        return _stack[index];
    } else return JENGA_ERR;
}

uint8_t JengaStack::size() {
    return _size;
}
