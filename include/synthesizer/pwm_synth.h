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

struct ControlShaper {
    float m;
    float b;
    float apply(float controlVal) {
        return (controlVal * m) + b;
    }
    ControlShaper(float newM, float newB) {
        m = newM;
        b = newB;
    }
};

enum SimpleControlBank : int {
    PWM_DUTY,
    INDIVIDUAL_MIXER,
    COMBINED_AMP_ENVELOPE,
    ETC1,
    OSC1_ENV,
    OSC2_ENV,
    OSC3_ENV,
    OSC4_ENV
};

class PwmSynth {
public:
    PwmSynth();
    void init();
    void noteOn(MidiNote note, uint8_t vel);
    void noteOff(MidiNote note);
    void controlChange(SimpleControlBank bank, uint8_t pos, float val);
    void controlChange(uint8_t pos, float val);
    void selectControlBank(uint8_t bank);

    void update();
protected:
    uint16_t getNextUpOscillator();

    // State
    bool _monoMode = false;
    VoiceState *voices;
    uint8_t _selectedBank = 0;

    // pwm duty control
    float _pwmBank[4] {0.5f, 0.5f, 0.5f, 0.5f};
    float _individualMixerBank[4] {1.0f, 1.0f, 1.0f, 1.0f};

    // amp envelope
    float _combinedAmpEnvBank[4] {0.0f, 0.0f, 1.0f, 0.0f};

    // amp mixer
    float _combinedAmpMixer[4] {1.0f, 1.0f, 1.0f, 1.0f};

    float _osc1EnvBank[4] {0.0f, 0.0f, 1.0f, 0.0f};
    float _osc2EnvBank[4] {0.0f, 0.0f, 1.0f, 0.0f};
    float _osc3EnvBank[4] {0.0f, 0.0f, 1.0f, 0.0f};
    float _osc4EnvBank[4] {0.0f, 0.0f, 1.0f, 0.0f};

    float* _simpleControlsBanks[8] {_pwmBank, _individualMixerBank, _combinedAmpEnvBank, _combinedAmpMixer,
                                    _osc1EnvBank, _osc2EnvBank, _osc3EnvBank, _osc4EnvBank};
    ControlShaper _simpleControlsBankShapers[4] {
        ControlShaper(2.0, -1.0),
        ControlShaper(1.0, 0.0),
        ControlShaper(1.0, 0.0),
        ControlShaper(20000.0, 0.0)
    };

    ControlShaper _envelopeADRShaper = ControlShaper(750.0, 0.0);
    ControlShaper _envelopeSShaper = ControlShaper(1.0, 0.0);
    void _updateControlBanks();
};

extern PwmSynth pwmSynth;

#endif //TEENSY_SYNTH_PWM_SYNTH_H
