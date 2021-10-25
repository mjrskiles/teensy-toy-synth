//
// Created by mjrsk on 10/22/2021.
//

#ifndef TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H
#define TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H

#include <Audio.h>

// GUItool: begin automatically generated code
extern AudioSynthWaveformDc     dc1;            //xy=55,776
extern AudioSynthWaveformDc     dc2;            //xy=64,849
extern AudioSynthWaveformDc     dc3;            //xy=67,924
extern AudioSynthWaveformDc     dc4;            //xy=84,1010
extern AudioSynthWaveformPWM    pwm4;           //xy=260,997
extern AudioSynthWaveformPWM    pwm2;           //xy=263,840
extern AudioSynthWaveformPWM    pwm1;           //xy=273,776
extern AudioSynthWaveformPWM    pwm3;           //xy=273,915
extern AudioSynthWaveformDc     dc_lpf1;            //xy=403,813
extern AudioSynthWaveformDc     dc_lpf2; //xy=403,881
extern AudioSynthWaveformDc     dc_lpf3; //xy=405,955
extern AudioSynthWaveformDc     dc_lpf4; //xy=406,1035
extern AudioFilterStateVariable lpf2; //xy=578,858
extern AudioFilterStateVariable lpf4; //xy=578,1028
extern AudioFilterStateVariable lpf1;        //xy=579,779
extern AudioFilterStateVariable lpf3; //xy=580,944
extern AudioMixer4              lpf_intermediate_mixer2; //xy=814,841
extern AudioMixer4              lpf_intermediate_mixer3; //xy=816,931
extern AudioMixer4              lpf_intermediate_mixer1;         //xy=817,746
extern AudioMixer4              lpf_intermediate_mixer4; //xy=820,1021
extern AudioEffectEnvelope      pwm_env1;      //xy=1032.5,755
extern AudioEffectEnvelope      pwm_env2; //xy=1053.75,838.75
extern AudioEffectEnvelope      pwm_env4; //xy=1065,1020
extern AudioEffectEnvelope      pwm_env3; //xy=1066.25,923.75
extern AudioMixer4              lpf_post_mixer;         //xy=1270.75,888.2500305175781
extern AudioSynthWaveformDc     dc_main_lpf;            //xy=1326.2501220703125,976
extern AudioFilterStateVariable main_lpf;        //xy=1427.0001220703125,883.2500305175781
extern AudioOutputI2S           i2s2; //xy=1585.08349609375,881.8611145019531
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
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;
extern AudioConnection          patchCord20;
extern AudioConnection          patchCord21;
extern AudioConnection          patchCord22;
extern AudioConnection          patchCord23;
extern AudioConnection          patchCord24;
extern AudioConnection          patchCord25;
extern AudioConnection          patchCord26;
extern AudioConnection          patchCord27;
extern AudioConnection          patchCord28;
extern AudioConnection          patchCord29;
extern AudioConnection          patchCord30;
extern AudioConnection          patchCord31;
extern AudioConnection          patchCord32;
extern AudioControlSGTL5000     sgtl5000_1;   //xy=784.2857142857142,642.8571428571428
// GUItool: end automatically generated code




#endif //TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H
