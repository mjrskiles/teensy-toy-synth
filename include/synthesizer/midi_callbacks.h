//
// Created by Michael Skiles on 10/15/21.
//

#ifndef TEENSY_SYNTH_MIDI_CALLBACKS_H
#define TEENSY_SYNTH_MIDI_CALLBACKS_H

#include <cstdint>
#include "synthesizer.h"

void cb_handleNoteOn(uint8_t channel, uint8_t note, uint8_t vel) {
    toySynth.setNoteOn(MidiNote(note), vel);
}

void cb_handleNoteoff(uint8_t channel, uint8_t note, uint8_t vel) {
    toySynth.setNoteOff(NOTE_AMINUS1); // TODO this will need to change for a poly synth
}

#endif //TEENSY_SYNTH_MIDI_CALLBACKS_H
