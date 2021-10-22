//
// Created by Michael Skiles on 10/22/21.
//

#ifndef TEENSY_SYNTH_PWM_SYNTH_H
#define TEENSY_SYNTH_PWM_SYNTH_H

#include "synth_signal_chain.h"
#include "buffers/luts.h"
#include "static_ordered_list.h"

class PwmSynth {
public:
    void noteOn(MidiNote note, uint8_t vel);
    void noteOff(MidiNote note);

protected:
    bool monoMode = false;
    StaticOrderedList<uint8_t> voiceIndexList = StaticOrderedList<uint8_t>();
};

#endif //TEENSY_SYNTH_PWM_SYNTH_H
