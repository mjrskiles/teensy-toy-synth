//
// Created by Michael Skiles on 9/28/21.
//

#ifndef SYNTH_VOICELIST_H
#define SYNTH_VOICELIST_H

#include <stdint.h>

const uint8_t MAX_VOICES = 8;
const uint8_t UNASSIGNED_VOICE_VALUE = 255;

class VoiceList {
public:
    VoiceList();

    VoiceList(uint8_t *triggeredInputIndices);

    uint8_t currentSize();
    uint8_t activeVoiceIndex();
    void addVoice(uint8_t index);
    bool removeVoice(uint8_t index); // returns true if the voice was removed
private:
    uint8_t _triggeredInputIndices[MAX_VOICES]{};
    void _removeAtLocation(uint8_t loc);
    void _init();
};


#endif //SYNTH_VOICELIST_H
