//
// Created by Michael Skiles on 10/23/21.
//

#include "synthesizer/synth_signal_chain.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoisePink      pink4;          //xy=1830,1673
AudioSynthNoisePink      pink2;          //xy=1836,970
AudioSynthNoisePink      pink3;          //xy=1842,1270
AudioSynthNoisePink      pink1;          //xy=1849,695
AudioSynthWaveformModulated wave2a; //xy=1848.333251953125,911.6666259765625
AudioSynthWaveformModulated wave3a; //xy=1850.333251953125,1217
AudioSynthWaveformModulated wave4a; //xy=1851.6666259765625,1578.333251953125
AudioSynthWaveformModulated wave1a;   //xy=1861.6666717529297,630.0000190734863
AudioMixer4              lpf_intermediate_mixer2; //xy=2086.33349609375,887.333251953125
AudioMixer4              lpf_intermediate_mixer3; //xy=2131,1243.9998779296875
AudioMixer4              lpf_intermediate_mixer4; //xy=2141.33349609375,1566.9998779296875
AudioMixer4              lpf_intermediate_mixer1; //xy=2147.666748046875,681.666748046875
AudioEffectEnvelope      pwm_env2;       //xy=2334.33349609375,920.333251953125
AudioEffectEnvelope      pwm_env1;       //xy=2382.666748046875,646.666748046875
AudioEffectEnvelope      pwm_env3;       //xy=2397,1251.9998779296875
AudioEffectEnvelope      pwm_env4;       //xy=2406.33349609375,1580.9998779296875
AudioSynthWaveformDc     dc_lpf3;        //xy=2457.000244140625,1375.3331298828125
AudioSynthWaveformDc     dc_lpf4;        //xy=2457.3333740234375,1713.9998779296875
AudioSynthWaveformDc     dc_lpf1;        //xy=2473.6668701171875,691.666748046875
AudioSynthWaveformDc     dc_lpf2;        //xy=2495.33349609375,1052.333251953125
AudioFilterStateVariable lpf2;           //xy=2583.33349609375,906.333251953125
AudioFilterStateVariable lpf4;           //xy=2608.33349609375,1586.9998779296875
AudioFilterStateVariable lpf3;           //xy=2615,1255.9998779296875
AudioFilterStateVariable lpf1;           //xy=2683.333465576172,640.3334197998047
AudioMixer4              lpf_post_mixer; //xy=2918.3333740234375,1145.3333096504211
AudioFilterStateVariable lpf_master;        //xy=3176.25,1213.75
AudioOutputI2S           i2s2;           //xy=3503.3333740234375,1152.083251953125
AudioConnection          patchCord1(pink4, 0, lpf_intermediate_mixer4, 1);
AudioConnection          patchCord2(pink2, 0, lpf_intermediate_mixer2, 1);
AudioConnection          patchCord3(pink3, 0, lpf_intermediate_mixer3, 1);
AudioConnection          patchCord4(pink1, 0, lpf_intermediate_mixer1, 1);
AudioConnection          patchCord5(wave2a, 0, lpf_intermediate_mixer2, 0);
AudioConnection          patchCord6(wave3a, 0, lpf_intermediate_mixer3, 0);
AudioConnection          patchCord7(wave4a, 0, lpf_intermediate_mixer4, 0);
AudioConnection          patchCord8(wave1a, 0, lpf_intermediate_mixer1, 0);
AudioConnection          patchCord9(lpf_intermediate_mixer2, pwm_env2);
AudioConnection          patchCord10(lpf_intermediate_mixer3, pwm_env3);
AudioConnection          patchCord11(lpf_intermediate_mixer4, pwm_env4);
AudioConnection          patchCord12(lpf_intermediate_mixer1, pwm_env1);
AudioConnection          patchCord13(pwm_env2, 0, lpf2, 0);
AudioConnection          patchCord14(pwm_env1, 0, lpf1, 0);
AudioConnection          patchCord15(pwm_env3, 0, lpf3, 0);
AudioConnection          patchCord16(pwm_env4, 0, lpf4, 0);
AudioConnection          patchCord17(dc_lpf3, 0, lpf3, 1);
AudioConnection          patchCord18(dc_lpf4, 0, lpf4, 1);
AudioConnection          patchCord19(dc_lpf1, 0, lpf1, 1);
AudioConnection          patchCord20(dc_lpf2, 0, lpf2, 1);
AudioConnection          patchCord21(lpf2, 0, lpf_post_mixer, 1);
AudioConnection          patchCord22(lpf4, 0, lpf_post_mixer, 3);
AudioConnection          patchCord23(lpf3, 1, lpf_post_mixer, 2);
AudioConnection          patchCord24(lpf1, 0, lpf_post_mixer, 0);
AudioConnection          patchCord25(lpf_post_mixer, 0, lpf_master, 0);
AudioConnection          patchCord26(lpf_master, 0, i2s2, 0);
AudioConnection          patchCord27(lpf_master, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2027.7777777777778,1948.888888888889
// GUItool: end automatically generated code;
