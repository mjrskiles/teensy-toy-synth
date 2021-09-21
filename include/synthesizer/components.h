//
// Created by mjrsk on 9/20/2021.
//

#ifndef SYNTH_COMPONENTS_H
#define SYNTH_COMPONENTS_H

#include <Audio.h>

AudioSynthWaveform       squarewaveBase;      //xy=90,59
AudioSynthWaveformSine   phaseCtrl1;          //xy=99,237
AudioSynthWaveformModulated squarewavePhaseMod;   //xy=260,303
AudioEffectEnvelope      envelope2;      //xy=294,119
AudioEffectEnvelope      envelope1;      //xy=381,396
AudioMixer4              mixerEnv1;         //xy=482,113
AudioMixer4              mixerEnv2;         //xy=482,293
AudioMixer4              oscCombineMixer;         //xy=613,187
AudioSynthWaveformSine   lpfCtrl;          //xy=645,300
AudioFilterStateVariable lpf1;        //xy=781,191
AudioMixer4              mixer1;         //xy=984,193
AudioOutputI2S           i2s1;           //xy=1149,189
AudioConnection          patchCord1;
AudioConnection          patchCord2;
AudioConnection          patchCord3;
AudioConnection          patchCord4;
AudioConnection          patchCord5;
AudioConnection          patchCord6;
AudioConnection          patchCord7;
AudioConnection          patchCord8;
AudioConnection          patchCord9;
AudioConnection          patchCord10;
AudioConnection          patchCord11;
AudioConnection          patchCord12;
AudioConnection          patchCord13;
AudioConnection          patchCord14;
AudioControlSGTL5000     sgtl5000_1;

#endif //SYNTH_COMPONENTS_H
