//
// Created by Michael Skiles on 10/22/21.
//

#ifndef TEENSY_SYNTH_PWM_SYNTH_H
#define TEENSY_SYNTH_PWM_SYNTH_H

#include "synth_signal_chain.h"
#include "buffers/luts.h"
#include "static_ordered_list.h"

#define NUM_OSCILLATORS 4

struct VoiceState {
    VoiceState(AudioSynthWaveformPWM *oscillator, AudioEffectEnvelope* envelope, uint8_t voiceIndex, MidiNote note, bool active);

    AudioSynthWaveformPWM* oscillator;
    AudioEffectEnvelope* envelope;
    uint8_t voiceIndex;
    MidiNote note;
    bool active = false;
};

class PwmSynth {
public:
    PwmSynth();
    void init();
    void noteOn(MidiNote note, uint8_t vel);
    void noteOff(MidiNote note);
    void update();
protected:
    uint16_t getNextUpOscillator();

    bool _monoMode = false;

    VoiceState *voices;

    // pwm duty control
    float _pwmControl1 = 0.5;
    float _pwmControl2 = 0.5;
    float _pwmControl3 = 0.5;
    float _pwmControl4 = 0.5;

    // Individual Low Pass Filters // TODO what is a good default value
    float _preMixLpf1 = 1.0;
    float _preMixLpf2 = 1.0;
    float _preMixLpf3 = 1.0;
    float _preMixLpf4 = 1.0;

    // amp envelope
    float _ampEnv_A = 0.0;
    float _ampEnv_D = 0.0;
    float _ampEnv_S = 1.0;
    float _ampEnv_R = 0.0;

    // filter envelope
    float _filterEnv_A = 0.0;
    float _filterEnv_D = 0.0;
    float _filterEnv_S = 1.0;
    float _filterEnv_R = 0.0;
};

extern PwmSynth pwmSynth;

#endif //TEENSY_SYNTH_PWM_SYNTH_H
