//
// Created by Michael Skiles on 10/22/21.
//

#include <model/buffers.h>
#include <model/buf_utils.h>
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

    lpf1.frequency(10000.0);
//    lpf2.frequency(20000.0);
//    lpf3.frequency(20000.0);
//    lpf4.frequency(20000.0);
//
//    lpf_intermediate_mixer1.gain(0, 0.0);
//    lpf_intermediate_mixer1.gain(1, 1.0);
//
    main_lpf.frequency(10000.0);

    for (int i = 0; i < NUM_OSCILLATORS; i++) {
        voices[i].envelope->release(0.0);
    }
}

void PwmSynth::controlChange(SimpleControlBank bank, uint8_t pos, float val) {
    _simpleControlsBanks[bank][pos] = val;
    _updateControlBanks();
}

void PwmSynth::controlChange(uint8_t pos, float val) {
    controlChange((SimpleControlBank)_selectedBank, pos, val);
}

void PwmSynth::selectControlBank(uint8_t bank) {
    _selectedBank = bank;
}

void PwmSynth::_updateControlBanks() {
    selectControlBank(bankSelectByte);

    // comes in from 0.0 to 1.0
    _simpleControlsBanks[_selectedBank][0] = analog_control_1;
    _simpleControlsBanks[_selectedBank][1] = analog_control_2;
    _simpleControlsBanks[_selectedBank][2] = analog_control_3;
    _simpleControlsBanks[_selectedBank][3] = analog_control_4;

    dc1.amplitude(_simpleControlsBankShapers[PWM_DUTY].apply(_simpleControlsBanks[PWM_DUTY][0]));
    dc2.amplitude(_simpleControlsBankShapers[PWM_DUTY].apply(_simpleControlsBanks[PWM_DUTY][1]));
    dc3.amplitude(_simpleControlsBankShapers[PWM_DUTY].apply(_simpleControlsBanks[PWM_DUTY][2]));
    dc4.amplitude(_simpleControlsBankShapers[PWM_DUTY].apply(_simpleControlsBanks[PWM_DUTY][3]));


    dc_lpf1.amplitude(_lpfCtrlShaper.apply(_simpleControlsBanks[INDIVIDUAL_LPF][0]));
    dc_lpf2.amplitude(_lpfCtrlShaper.apply(_simpleControlsBanks[INDIVIDUAL_LPF][1]));
    dc_lpf3.amplitude(_lpfCtrlShaper.apply(_simpleControlsBanks[INDIVIDUAL_LPF][2]));
    dc_lpf4.amplitude(_lpfCtrlShaper.apply(_simpleControlsBanks[INDIVIDUAL_LPF][3]));

//    lpf1.frequency(_lpfCtrlShaper.apply(_simpleControlsBanks[INDIVIDUAL_LPF][0]));
//    lpf2.frequency(_lpfCtrlShaper.apply(_simpleControlsBanks[INDIVIDUAL_LPF][1]));
//    lpf3.frequency(_lpfCtrlShaper.apply(_simpleControlsBanks[INDIVIDUAL_LPF][2]));
//    lpf4.frequency(_lpfCtrlShaper.apply(_simpleControlsBanks[INDIVIDUAL_LPF][3]));

    lpf_post_mixer.gain(0, _mixerShaper.apply(_simpleControlsBanks[COMBINED_MIXER][0]));
    lpf_post_mixer.gain(1, _mixerShaper.apply(_simpleControlsBanks[COMBINED_MIXER][1]));
    lpf_post_mixer.gain(2, _mixerShaper.apply(_simpleControlsBanks[COMBINED_MIXER][2]));
    lpf_post_mixer.gain(3, _mixerShaper.apply(_simpleControlsBanks[COMBINED_MIXER][3]));

    dc_main_lpf.amplitude(_lpfCtrlShaper.apply(_simpleControlsBanks[ETC1][0]));

    pwm_env1.attack(_envelopeADRShaper.apply(_simpleControlsBanks[OSC1_ENV][0]));
    pwm_env1.decay(_envelopeADRShaper.apply(_simpleControlsBanks[OSC1_ENV][1]));
    pwm_env1.sustain(_envelopeSShaper.apply(_simpleControlsBanks[OSC1_ENV][2]));
    pwm_env1.release(_envelopeADRShaper.apply(_simpleControlsBanks[OSC1_ENV][3]));

    pwm_env2.attack(_envelopeADRShaper.apply(_simpleControlsBanks[OSC2_ENV][0]));
    pwm_env2.decay(_envelopeADRShaper.apply(_simpleControlsBanks[OSC2_ENV][1]));
    pwm_env2.sustain(_envelopeSShaper.apply(_simpleControlsBanks[OSC2_ENV][2]));
    pwm_env2.release(_envelopeADRShaper.apply(_simpleControlsBanks[OSC2_ENV][3]));

    pwm_env3.attack(_envelopeADRShaper.apply(_simpleControlsBanks[OSC3_ENV][0]));
    pwm_env3.decay(_envelopeADRShaper.apply(_simpleControlsBanks[OSC3_ENV][1]));
    pwm_env3.sustain(_envelopeSShaper.apply(_simpleControlsBanks[OSC3_ENV][2]));
    pwm_env3.release(_envelopeADRShaper.apply(_simpleControlsBanks[OSC3_ENV][3]));

    pwm_env4.attack(_envelopeADRShaper.apply(_simpleControlsBanks[OSC4_ENV][0]));
    pwm_env4.decay(_envelopeADRShaper.apply(_simpleControlsBanks[OSC4_ENV][1]));
    pwm_env4.sustain(_envelopeSShaper.apply(_simpleControlsBanks[OSC4_ENV][2]));
    pwm_env4.release(_envelopeADRShaper.apply(_simpleControlsBanks[OSC4_ENV][3]));

}

bool PwmSynth::isControlChangeActive() const {
    return _controlChangeActive;
}

void PwmSynth::setControlChangeActive(bool controlChangeActive) {
    _controlChangeActive = controlChangeActive;
}
