//
// Created by Michael Skiles on 9/28/21.
//

#include "synthesizer/VoiceList.h"
#include "Logr.h"

Logr logr = Logr();

// The list gets filled from the end so each index matches its precedence
uint8_t VoiceList::currentSize() {
    int i = 0;
    uint8_t val = UNASSIGNED_VOICE_VALUE;
    while (val == UNASSIGNED_VOICE_VALUE && i < MAX_VOICES) {
        val = _triggeredInputIndices[i];
        i++;
    }
    return MAX_VOICES - i; // i will be at least 1
}

/*
 * !!! Returns the index into the SNAPSHOT BUFFER, not the voice list.
 */
uint8_t VoiceList::activeVoiceIndex() {
    for (int i = 0; i < MAX_VOICES; i++) {
        if (_triggeredInputIndices[i] != UNASSIGNED_VOICE_VALUE) return _triggeredInputIndices[i];
    }
    return UNASSIGNED_VOICE_VALUE;
}

void VoiceList::addVoice(uint8_t index) {
    uint8_t size = currentSize();
    if (size >= MAX_VOICES) logr.debug("Voice List is full");
    else {
        _triggeredInputIndices[MAX_VOICES - size - 1] = index;
    }
}

// Remove the voice whose stored value is equal to 'index'
bool VoiceList::removeVoice(uint8_t index) {
    uint8_t prev = 0;
    int i = MAX_VOICES - 1;
    while (i >= 0 && prev != UNASSIGNED_VOICE_VALUE) {
        if (_triggeredInputIndices[i] == index) {
            _removeAtLocation(i);
            return true;
        }
        prev = _triggeredInputIndices[i];
        i--;
    }
    return false;
}

void VoiceList::_removeAtLocation(uint8_t loc) {
    Serial.println("Size before removing:");
    Serial.println(currentSize());
    if (loc >= (MAX_VOICES - 1) || loc == 0) {
        _triggeredInputIndices[(loc == 0) ? 0 : (MAX_VOICES - 1)] = UNASSIGNED_VOICE_VALUE;
        return;
    } else {
        int i = loc;
        uint8_t next;
        do {
            next = _triggeredInputIndices[i - 1];
            _triggeredInputIndices[i] = next;
            i--;
        } while (i >= 0 && _triggeredInputIndices[i] != UNASSIGNED_VOICE_VALUE);
    }
    Serial.println("Size after removing:");
    Serial.println(currentSize());
}

VoiceList::VoiceList(uint8_t *triggeredInputIndices) : _triggeredInputIndices(triggeredInputIndices) {
    _init();
}

void VoiceList::_init() {
    for (int i = 0; i < MAX_VOICES; i++) {
        _triggeredInputIndices[i] = UNASSIGNED_VOICE_VALUE;
    }
}
