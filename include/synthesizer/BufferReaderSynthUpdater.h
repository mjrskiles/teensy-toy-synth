//
// Created by Michael Skiles on 9/22/21.
//

#ifndef TEENSY_TOY_SYNTH_BUFFERREADERSYNTHUPDATER_H
#define TEENSY_TOY_SYNTH_BUFFERREADERSYNTHUPDATER_H

#include <inttypes.h>

class Updater {
public:
    uint16_t buttonWordBuffer = 0;
    void updateInputsFromBuffer();
};

#endif //TEENSY_TOY_SYNTH_BUFFERREADERSYNTHUPDATER_H
