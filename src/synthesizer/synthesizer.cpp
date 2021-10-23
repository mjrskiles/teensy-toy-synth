//
// Created by Michael Skiles on 9/16/21.
//

#include "synthesizer/synthesizer.h"

// GUItool: begin automatically generated code
//AudioSynthWaveform       waveform1;      //xy=90,59
//AudioSynthWaveformSine   phaseCtrl1;          //xy=99,237
//AudioSynthWaveformModulated waveform2;   //xy=260,303
//AudioEffectEnvelope      waveform1Envelope;      //xy=294,119
//AudioEffectEnvelope      waveform2Envelope;      //xy=381,396
//AudioMixer4              mixerEnv1;         //xy=482,113
//AudioMixer4              mixerEnv2;         //xy=482,293
//AudioMixer4              oscCombineMixer;         //xy=613,187
//AudioSynthWaveformSine   lpfCtrl;          //xy=645,300
//AudioFilterStateVariable lpf1;        //xy=781,191
//AudioMixer4              mixer1;         //xy=984,193
//AudioOutputI2S           i2s1;           //xy=1149,189
//AudioConnection          patchCord1 = AudioConnection(waveform1, waveform1Envelope);
//AudioConnection          patchCord2 = AudioConnection(waveform1, 0, mixerEnv1, 0);
//AudioConnection          patchCord3 = AudioConnection(phaseCtrl1, 0, waveform2, 0);
//AudioConnection          patchCord4 = AudioConnection(waveform2, waveform2Envelope);
//AudioConnection          patchCord5 = AudioConnection(waveform2, 0, mixerEnv2, 0);
//AudioConnection          patchCord6 = AudioConnection(waveform1Envelope, 0, mixerEnv1, 1);
//AudioConnection          patchCord7 = AudioConnection(waveform2Envelope, 0, mixerEnv2, 1);
//AudioConnection          patchCord8 = AudioConnection(mixerEnv1, 0, oscCombineMixer, 0);
//AudioConnection          patchCord9 = AudioConnection(mixerEnv2, 0, oscCombineMixer, 1);
//AudioConnection          patchCord10 = AudioConnection(oscCombineMixer, 0, lpf1, 0);
//AudioConnection          patchCord11 = AudioConnection(lpfCtrl, 0, lpf1, 1);
//AudioConnection          patchCord12 = AudioConnection(lpf1, 0, mixer1, 0);
//AudioConnection          patchCord13 = AudioConnection(mixer1, 0, i2s1, 0);
//AudioConnection          patchCord14 = AudioConnection(mixer1, 0, i2s1, 1);
//AudioControlSGTL5000     sgtl5000_1;     //xy=585,481
//// GUItool: end automatically generated code

void ToySynth::synth_init() {

    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
//    sgtl5000_1.enable();
//    sgtl5000_1.volume(1.0);
//    waveform1.begin(WAVEFORM_SQUARE);
}

void ToySynth::setNoteOn(MidiNote note, uint8_t velocity) {
    activeNote = note;
    float freq = midi_frequencies[note];
//    Serial.printf("Setting voice on with freq: %8.2f\n", freq);
//    waveform1.frequency(freq);
//    waveform1.amplitude(1.0);
//    waveform1Envelope.noteOn();
}

void ToySynth::setNoteOff(MidiNote note) {
    Serial.println("Setting voice to off.");
//    waveform1Envelope.noteOff();
}

/*
 * The synthesizer gets notified whenever there is a relevant I/O change. We need to check the buffers and take
 * appropriate action
 */
void ToySynth::notify() {
    // Check which notes are newly on and turn on the voice
    uint16_t newlyOn = whichBitsAreNewlyOn(keyboard_io_word_previous, keyboard_io_word);
    for (int i = 0; i < 16; i++) {
        if (isOneAtIndex(newlyOn, i)) {
            Serial.println("Note press");
            uint8_t logicalLoc = physical_to_logical_button_loc[i];
            MidiNote note = _currentScale[logicalLoc];
            setNoteOn(note, 127);
        }
    }

    // For now just turn off the voice if there are no key presses
    if (!keyboard_io_word) setNoteOff(NOTE_AMINUS1);
}

ToySynth::ToySynth() {}
