//
// Created by Michael Skiles on 9/28/21.
//

#include "synthesizer/VoiceList.h"
#include "Logr.h"

Logr logr1 = Logr();

// The list gets filled from the end so each index matches its precedence
uint8_t VoiceList::currentSize() {
    int i = 0;
    for (i; i < MAX_VOICES; i++) {
        if (_triggeredInputIndices[i] != UNASSIGNED_VOICE_VALUE) {
            break;
        }
    }
    return MAX_VOICES - i;
}

bool VoiceList::isEmpty() {
    return (currentSize() == 0);
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
    if (size >= MAX_VOICES) logr1.debug("Voice List is full");
    else {
        _triggeredInputIndices[MAX_VOICES - size - 1] = index;
    }
    Serial.println("Trigged input buffer loc:");
    Serial.println(MAX_VOICES - size - 1);
    Serial.println("value at loc:");
    Serial.println(_triggeredInputIndices[MAX_VOICES - size - 1]);
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

void VoiceList::_init() {
    for (int i = 0; i < MAX_VOICES; i++) {
        _triggeredInputIndices[i] = UNASSIGNED_VOICE_VALUE;
    }
}

VoiceList::VoiceList() {
    _init();
}
