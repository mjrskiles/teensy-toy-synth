//
// Created by mjrsk on 10/22/2021.
//

#ifndef TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H
#define TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H

#include <Audio.h>

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
// GUItool: begin automatically generated code
extern AudioSynthNoisePink      pink4;          //xy=1830,1673
extern AudioSynthNoisePink      pink2;          //xy=1836,970
extern AudioSynthNoisePink      pink3;          //xy=1842,1270
extern AudioSynthNoisePink      pink1;          //xy=1849,695
extern AudioSynthWaveformModulated wave2a; //xy=1848.333251953125,911.6666259765625
extern AudioSynthWaveformModulated wave3a; //xy=1850.333251953125,1217
extern AudioSynthWaveformModulated wave4a; //xy=1851.6666259765625,1578.333251953125
extern AudioSynthWaveformModulated wave1a;   //xy=1861.6666717529297,630.0000190734863
extern AudioMixer4              lpf_intermediate_mixer2; //xy=2086.33349609375,887.333251953125
extern AudioMixer4              lpf_intermediate_mixer3; //xy=2131,1243.9998779296875
extern AudioMixer4              lpf_intermediate_mixer4; //xy=2141.33349609375,1566.9998779296875
extern AudioMixer4              lpf_intermediate_mixer1; //xy=2147.666748046875,681.666748046875
extern AudioEffectEnvelope      pwm_env2;       //xy=2334.33349609375,920.333251953125
extern AudioEffectEnvelope      pwm_env1;       //xy=2382.666748046875,646.666748046875
extern AudioEffectEnvelope      pwm_env3;       //xy=2397,1251.9998779296875
extern AudioEffectEnvelope      pwm_env4;       //xy=2406.33349609375,1580.9998779296875
extern AudioSynthWaveformDc     dc_lpf3;        //xy=2457.000244140625,1375.3331298828125
extern AudioSynthWaveformDc     dc_lpf4;        //xy=2457.3333740234375,1713.9998779296875
extern AudioSynthWaveformDc     dc_lpf1;        //xy=2473.6668701171875,691.666748046875
extern AudioSynthWaveformDc     dc_lpf2;        //xy=2495.33349609375,1052.333251953125
extern AudioFilterStateVariable lpf2;           //xy=2583.33349609375,906.333251953125
extern AudioFilterStateVariable lpf4;           //xy=2608.33349609375,1586.9998779296875
extern AudioFilterStateVariable lpf3;           //xy=2615,1255.9998779296875
extern AudioFilterStateVariable lpf1;           //xy=2683.333465576172,640.3334197998047
extern AudioMixer4              lpf_post_mixer; //xy=2918.3333740234375,1145.3333096504211
extern AudioFilterStateVariable lpf_master;        //xy=3176.25,1213.75
extern AudioOutputI2S           i2s2;           //xy=3503.3333740234375,1152.083251953125
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
extern AudioControlSGTL5000     sgtl5000_1;     //xy=2027.7777777777778,1948.888888888889
// GUItool: end automatically generated codecode




#endif //TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H
