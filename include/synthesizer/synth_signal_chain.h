//
// Created by mjrsk on 10/22/2021.
//

#ifndef TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H
#define TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=55,776
AudioSynthWaveformDc     dc2;            //xy=64,849
AudioSynthWaveformDc     dc3;            //xy=67,924
AudioSynthWaveformDc     dc4;            //xy=84,1010
AudioSynthWaveformPWM    pwm4;           //xy=260,997
AudioSynthWaveformPWM    pwm2;           //xy=263,840
AudioSynthWaveformPWM    pwm1;           //xy=273,776
AudioSynthWaveformPWM    pwm3;           //xy=273,915
AudioSynthWaveformDc     dc_lpf1;            //xy=403,813
AudioSynthWaveformDc     dc_lpf2; //xy=403,881
AudioSynthWaveformDc     dc_lpf3; //xy=405,955
AudioSynthWaveformDc     dc_lpf4; //xy=406,1035
AudioFilterStateVariable lpf2; //xy=578,858
AudioFilterStateVariable lpf4; //xy=578,1028
AudioFilterStateVariable lpf1;        //xy=579,779
AudioFilterStateVariable lpf3; //xy=580,944
AudioMixer4              lpf_intermediate_mixer2; //xy=814,841
AudioMixer4              lpf_intermediate_mixer3; //xy=816,931
AudioMixer4              lpf_intermediate_mixer1;         //xy=817,746
AudioMixer4              lpf_intermediate_mixer4; //xy=820,1021
AudioMixer4              lpf_post_mixer;         //xy=1077,852
AudioSynthWaveformDc     dc_main_lpf;            //xy=1090,936
AudioFilterStateVariable main_lpf;        //xy=1272,892
AudioOutputI2S           i2s2; //xy=1448,892
AudioConnection          patchCord1(dc1, pwm1);
AudioConnection          patchCord2(dc2, pwm2);
AudioConnection          patchCord3(dc3, pwm3);
AudioConnection          patchCord4(dc4, pwm4);
AudioConnection          patchCord5(pwm4, 0, lpf4, 0);
AudioConnection          patchCord6(pwm4, 0, lpf_intermediate_mixer4, 0);
AudioConnection          patchCord7(pwm2, 0, lpf2, 0);
AudioConnection          patchCord8(pwm2, 0, lpf_intermediate_mixer2, 0);
AudioConnection          patchCord9(pwm1, 0, lpf1, 0);
AudioConnection          patchCord10(pwm1, 0, lpf_intermediate_mixer1, 0);
AudioConnection          patchCord11(pwm3, 0, lpf3, 0);
AudioConnection          patchCord12(pwm3, 0, lpf_intermediate_mixer3, 0);
AudioConnection          patchCord13(dc_lpf1, 0, lpf1, 1);
AudioConnection          patchCord14(dc_lpf2, 0, lpf2, 1);
AudioConnection          patchCord15(dc_lpf3, 0, lpf3, 1);
AudioConnection          patchCord16(dc_lpf4, 0, lpf4, 1);
AudioConnection          patchCord17(lpf2, 0, lpf_intermediate_mixer2, 1);
AudioConnection          patchCord18(lpf4, 0, lpf_intermediate_mixer4, 1);
AudioConnection          patchCord19(lpf1, 0, lpf_intermediate_mixer1, 1);
AudioConnection          patchCord20(lpf3, 0, lpf_intermediate_mixer3, 1);
AudioConnection          patchCord21(lpf_intermediate_mixer2, 0, lpf_post_mixer, 1);
AudioConnection          patchCord22(lpf_intermediate_mixer3, 0, lpf_post_mixer, 2);
AudioConnection          patchCord23(lpf_intermediate_mixer1, 0, lpf_post_mixer, 0);
AudioConnection          patchCord24(lpf_intermediate_mixer4, 0, lpf_post_mixer, 3);
AudioConnection          patchCord25(lpf_post_mixer, 0, main_lpf, 0);
AudioConnection          patchCord26(dc_main_lpf, 0, main_lpf, 1);
AudioConnection          patchCord27(main_lpf, 0, i2s2, 0);
AudioConnection          patchCord28(main_lpf, 0, i2s2, 1);
AudioControlSGTL5000     e77e444f.6eb68; //xy=589,1186
// GUItool: end automatically generated code


#endif //TEENSY_SYNTH_SYNTH_SIGNAL_CHAIN_H
