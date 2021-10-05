//
// Created by Michael Skiles on 9/16/21.
//

#include "synthesizer/synthesizer.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       squarewaveBase;      //xy=90,59
AudioSynthWaveformSine   phaseCtrl1;          //xy=99,237
AudioSynthWaveformModulated triwaveBase;   //xy=260,303
AudioEffectEnvelope      envelope2;      //xy=294,119
AudioEffectEnvelope      envelope1;      //xy=381,396
AudioMixer4              mixerEnv1;         //xy=482,113
AudioMixer4              mixerEnv2;         //xy=482,293
AudioMixer4              oscCombineMixer;         //xy=613,187
AudioSynthWaveformSine   lpfCtrl;          //xy=645,300
AudioFilterStateVariable lpf1;        //xy=781,191
AudioMixer4              mixer1;         //xy=984,193
AudioOutputI2S           i2s1;           //xy=1149,189
AudioConnection          patchCord1 = AudioConnection(squarewaveBase, envelope2);
AudioConnection          patchCord2 = AudioConnection(squarewaveBase, 0, mixerEnv1, 0);
AudioConnection          patchCord3 = AudioConnection(phaseCtrl1, 0, triwaveBase, 0);
AudioConnection          patchCord4 = AudioConnection(triwaveBase, envelope1);
AudioConnection          patchCord5 = AudioConnection(triwaveBase, 0, mixerEnv2, 0);
AudioConnection          patchCord6 = AudioConnection(envelope2, 0, mixerEnv1, 1);
AudioConnection          patchCord7 = AudioConnection(envelope1, 0, mixerEnv2, 1);
AudioConnection          patchCord8 = AudioConnection(mixerEnv1, 0, oscCombineMixer, 0);
AudioConnection          patchCord9 = AudioConnection(mixerEnv2, 0, oscCombineMixer, 1);
AudioConnection          patchCord10 = AudioConnection(oscCombineMixer, 0, lpf1, 0);
AudioConnection          patchCord11 = AudioConnection(lpfCtrl, 0, lpf1, 1);
AudioConnection          patchCord12 = AudioConnection(lpf1, 0, mixer1, 0);
AudioConnection          patchCord13 = AudioConnection(mixer1, 0, i2s1, 0);
AudioConnection          patchCord14 = AudioConnection(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=585,481
//// GUItool: end automatically generated code

const char *mcpLower8Name = "MCP23008: Lower";
const char *mcpUpper8Name = "MCP23008: Upper";
const char *mcpPeriphName = "MCP23008: Peripheral";

extern InputSnapshotBool INPUT_BUFFER_BOOL[];

void ToySynth::synth_init() {

    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
    AudioMemory(24);

    sgtl5000_1.enable();
    sgtl5000_1.volume(1.0);
    squarewaveBase.begin(WAVEFORM_SQUARE);
    for (int i = 0; i < INPUT_BUFFER_SIZE_BOOLEAN; i++) {
        INPUT_BUFFER_BOOL[i].setName(INPUT_NAMES_BOOL[i]);
        INPUT_BUFFER_BOOL[i].setState(false);
        INPUT_BUFFER_BOOL[i].setFromIndex(i);
        // initialize the buffer to a 0 state
    }
}

void ToySynth::setVoiceOn(float frequency) {
    Serial.printf("Setting voice on with freq: %8.2f\n", frequency);
    squarewaveBase.frequency(frequency);
    squarewaveBase.amplitude(1.0);
    if (_active_voices.size() == 0) envelope2.noteOn();
}

void ToySynth::setVoiceOff() {
    Serial.println("Setting mono voice to off.");
//    squarewaveBase.amplitude(0.0);
    envelope2.noteOff();
}

void ToySynth::notify() {
    // TODO finish this function to respond to IO changes
    //
    // can't just check if the new word < old word because there could be a button release higher than a still pressed
    // button. Is it worth passing in PRESS | RELEASE to notify()?
    // How can we tell which key press is the new one?
    // Compare against the stack?
    // It's almost inevitable
    Serial.printf("Old IO word: %x\n", keyboard_io_word_previous);
    Serial.printf("New IO word: %x\n", keyboard_io_word);
    uint16_t new_state_mask = keyboard_io_word_previous ^ keyboard_io_word;
//    Serial.printf("1 Active voices size: %n\n", _active_voices.size());
    if (new_state_mask) { // if there are 1s in this word it means there have been changes. don't know if press or release yet
        for (int i = 0; i < JENGA_STACK_SIZE_MAX; i++) {
            if (new_state_mask & logical_loc_to_mask[i]) {
                // determine press or release
                if (keyboard_io_word & logical_loc_to_mask[i]) {
                    // Press
                    Serial.println("Note press");
                    MidiNotes note = _currentScale[i];
                    float freq = midi_frequencies[note];
                    setVoiceOn(freq);
                    _active_voices.push(i);
//                    Serial.printf("2 Active voices size: %n\n", _active_voices.size());
                } else if (keyboard_io_word_previous & logical_loc_to_mask[i]) { // was the key on in the last state? turn it off
                    // Release
                    Serial.println("Note release");
                    _active_voices.removeByValue(i);
//                    Serial.printf("3 Active voices size: %n\n", _active_voices.size());
                    if (_active_voices.size() == 0) {
                        setVoiceOff();
                    }
                }
            }
        }
    }
    Serial.printf("Active voices size: %x\n", _active_voices.size());
}

ToySynth::ToySynth(const JengaStack &activeVoices) : _active_voices(activeVoices) {}
