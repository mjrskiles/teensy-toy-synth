//
// Created by Michael Skiles on 9/16/21.
//

#ifndef SYNTH_SYNTHESIZER_H
#define SYNTH_SYNTHESIZER_H

#include <Audio.h>
#include <io/InputSnapshot.h>
#include "synth_defines.h"

// GUItool: begin automatically generated code
extern AudioSynthWaveform       squarewaveBase;      //xy=90,59
extern AudioSynthWaveformSine   phaseCtrl1;          //xy=99,237
extern AudioSynthWaveformModulated triwaveBase;   //xy=260,303
extern AudioEffectEnvelope      envelope2;      //xy=294,119
extern AudioEffectEnvelope      envelope1;      //xy=381,396
extern AudioMixer4              mixerEnv1;         //xy=482,113
extern AudioMixer4              mixerEnv2;         //xy=482,293
extern AudioMixer4              oscCombineMixer;         //xy=613,187
extern AudioSynthWaveformSine   lpfCtrl;          //xy=645,300
extern AudioFilterStateVariable lpf1;        //xy=781,191
extern AudioMixer4              mixer1;         //xy=984,193
extern AudioOutputI2S           i2s1;           //xy=1149,189
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioControlSGTL5000     sgtl5000_1;
//// GUItool: end automatically generated code

class ToySynth {
public:
    void synth_init();
    void setVoiceOn(float frequency);
    void setVoiceOff();
};



#endif //SYNTH_SYNTHESIZER_H
