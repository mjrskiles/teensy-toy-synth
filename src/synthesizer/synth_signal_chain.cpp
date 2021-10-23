//
// Created by Michael Skiles on 10/23/21.
//

#include "synthesizer/synth_signal_chain.h"

AudioSynthWaveformDc     dc4;            //xy=55,418.28568840026855
AudioSynthWaveformDc     dc1;            //xy=56.857147216796875,188.14285278320312
AudioSynthWaveformDc     dc3;            //xy=56.28572463989258,333.7142963409424
AudioSynthWaveformDc     dc2;            //xy=59.0000114440918,258.7142906188965
AudioSynthWaveformPWM    pwm1;           //xy=223.57144165039062,169.71429443359375
AudioEffectEnvelope      pwm_env3; //xy=257,363
AudioEffectEnvelope      pwm_env4; //xy=266,458
AudioSynthWaveformPWM    pwm4;           //xy=273.5714340209961,406.7142958641052
AudioSynthWaveformPWM    pwm2;           //xy=276.5714340209961,249.71429586410522
AudioEffectEnvelope      pwm_env1;      //xy=283.28570556640625,209.71429443359375
AudioSynthWaveformPWM    pwm3;           //xy=286.5714340209961,324.7142958641052
AudioEffectEnvelope      pwm_env2; //xy=306,287
AudioMixer4              lpf_intermediate_mixer1; //xy=529.5714111328125,159.71429443359375
AudioMixer4              lpf_intermediate_mixer2; //xy=538.5714111328125,252.71429443359375
AudioMixer4              lpf_intermediate_mixer3; //xy=558.5714111328125,336.71429443359375
AudioMixer4              lpf_intermediate_mixer4; //xy=565.5714111328125,429.71429443359375
AudioMixer4              lpf_post_mixer; //xy=1090.571434020996,261.7142958641052
AudioEffectEnvelope      amp_envelope1;      //xy=1287.1428298950195,215.71429824829102
AudioMixer4              post_amp_env_mixer1;         //xy=1497.1429290771484,257.1428565979004
AudioEffectEnvelope      envelope2;      //xy=1499.9998931884766,351.4286241531372
AudioFilterStateVariable main_lpf;       //xy=1699.8569221496582,267.42861557006836
AudioOutputI2S           i2s2;           //xy=1885.8570404052734,237.42859268188477
AudioConnection          patchCord1(dc4, pwm4);
AudioConnection          patchCord2(dc1, pwm1);
AudioConnection          patchCord3(dc3, pwm3);
AudioConnection          patchCord4(dc2, pwm2);
AudioConnection          patchCord5(pwm1, pwm_env1);
//AudioConnection          patchCord6(pwm1, 0, lpf_intermediate_mixer1, 0);
AudioConnection          patchCord7(pwm_env3, 0, lpf_intermediate_mixer3, 1);
AudioConnection          patchCord8(pwm_env4, 0, lpf_intermediate_mixer4, 1);
//AudioConnection          patchCord9(pwm4, 0, lpf_intermediate_mixer4, 0);
AudioConnection          patchCord10(pwm4, pwm_env4);
//AudioConnection          patchCord11(pwm2, 0, lpf_intermediate_mixer2, 0);
AudioConnection          patchCord12(pwm2, pwm_env2);
AudioConnection          patchCord13(pwm_env1, 0, lpf_intermediate_mixer1, 1);
//AudioConnection          patchCord14(pwm3, 0, lpf_intermediate_mixer3, 0);
AudioConnection          patchCord15(pwm3, pwm_env3);
AudioConnection          patchCord16(pwm_env2, 0, lpf_intermediate_mixer2, 1);
AudioConnection          patchCord17(lpf_intermediate_mixer1, 0, lpf_post_mixer, 0);
AudioConnection          patchCord18(lpf_intermediate_mixer2, 0, lpf_post_mixer, 1);
AudioConnection          patchCord19(lpf_intermediate_mixer3, 0, lpf_post_mixer, 2);
AudioConnection          patchCord20(lpf_intermediate_mixer4, 0, lpf_post_mixer, 3);
AudioConnection          patchCord21(lpf_post_mixer, amp_envelope1);
AudioConnection          patchCord22(lpf_post_mixer, 0, post_amp_env_mixer1, 1);
AudioConnection          patchCord23(amp_envelope1, 0, post_amp_env_mixer1, 0);
AudioConnection          patchCord24(post_amp_env_mixer1, 0, main_lpf, 0);
AudioConnection          patchCord25(post_amp_env_mixer1, envelope2);
AudioConnection          patchCord26(envelope2, 0, main_lpf, 1);
AudioConnection          patchCord27(main_lpf, 0, i2s2, 0);
AudioConnection          patchCord28(main_lpf, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;