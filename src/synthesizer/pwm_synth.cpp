//
// Created by Michael Skiles on 10/22/21.
//

#include <buffers/buffers.h>
#include <buffers/buf_utils.h>
#include "synthesizer/pwm_synth.h"

void PwmSynth::noteOn(MidiNote note, uint8_t vel) {
    uint16_t nextUp = getNextUpOscillator();
    activeNote = note;
    voices[nextUp].note = note;
    float freq = midi_frequencies[note];
    voices[nextUp].oscillator->frequency(freq);
    voices[nextUp].oscillator->amplitude(1.0);
    voices[nextUp].envelope->noteOn();
    voices[nextUp].active = true;
}

void PwmSynth::noteOff(MidiNote note) {
    const lcd_char *namePointer = midi_note_names[activeNote];
    Serial.printf("Turning off note %s", namePointer);

    for (int i = 0; i < NUM_OSCILLATORS; i++) {
        if (voices[i].active && voices[i].note == note) {
            Serial.printf("... found note %s\n", namePointer);
            voices[i].envelope->noteOff();
            voices[i].active = false;
        }
    }
}

void PwmSynth::update() {
    // Check which notes are newly on and turn on the voice
    uint16_t newlyOn = whichBitsAreNewlyOn(keyboard_io_word_previous, keyboard_io_word);
    for (int i = 0; i < 16; i++) {
        if (isOneAtIndex(newlyOn, i)) {
            Serial.println("Note press");
            uint8_t logicalLoc = physical_to_logical_button_loc[i];
            MidiNote note = currentScale[logicalLoc];
            noteOn(note, 127);
        }
    }

    // Check which notes are newly off and turn on the voice
    uint16_t newlyOff = whichBitsAreNewlyOff(keyboard_io_word_previous, keyboard_io_word);
    for (int i = 0; i < 16; i++) {
        if (isOneAtIndex(newlyOff, i)) {
            Serial.println("Note release");
            uint8_t logicalLoc = physical_to_logical_button_loc[i];
            MidiNote note = currentScale[logicalLoc];
            noteOff(note);
        }
    }

    if (!keyboard_io_word) {
        for (int i = 0; i < NUM_OSCILLATORS; i++) {
            if (!voices[i].envelope->isActive()) {
                voices[i].oscillator->amplitude(0.0);
            }
        }
    }
}

uint16_t PwmSynth::getNextUpOscillator() {
    for (int i = 0; i < NUM_OSCILLATORS; i++) {
        if (!voices[i].active) {
            return i;
        }
    }
    return 0;
}

VoiceState::VoiceState(AudioSynthWaveformPWM *oscillator, AudioEffectEnvelope *envelope, uint8_t voiceIndex, MidiNote note, bool active) : oscillator(
        oscillator), envelope(envelope), voiceIndex(voiceIndex), note(note), active(active) {}

PwmSynth::PwmSynth()  {
    voices = vsa;
}

void PwmSynth::init() {
    sgtl5000_1.enable();
    sgtl5000_1.volume(1.0);

    for (int i = 0; i < NUM_OSCILLATORS; i++) {
        voices[i].envelope->release(0.0);
    }
}
