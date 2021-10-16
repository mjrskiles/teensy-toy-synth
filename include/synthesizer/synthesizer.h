//
// Created by Michael Skiles on 9/16/21.
//

#ifndef SYNTH_SYNTHESIZER_H
#define SYNTH_SYNTHESIZER_H

#include <Audio.h>
#include <io/InputSnapshot.h>
#include <io/notification_receiver.h>
#include "toy_defines.h"
#include "buffers/buffers.h"
#include "../../lib/JengaStack/JengaStack.h"
#include "buffers/luts.h"
#include "buffers/buf_utils.h"

// GUItool: begin automatically generated code
extern AudioSynthWaveform       waveform1;      //xy=90,59
extern AudioSynthWaveformSine   phaseCtrl1;          //xy=99,237
extern AudioSynthWaveformModulated waveform2;   //xy=260,303
extern AudioEffectEnvelope      waveform1Envelope;      //xy=294,119
extern AudioEffectEnvelope      waveform2Envelope;      //xy=381,396
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

class ToySynth : public NotificationReceiver {
public:
    ToySynth();

    void synth_init();

    /*
     * Midi Interface
     */
    void setNoteOn(MidiNote note, uint8_t velocity);
    void setNoteOff(MidiNote note);

    /*
     * Direct I/O interface
     */
    void notify();
private:
    JengaStack _active_voices;
    MidiNote *_currentScale = BbMajorScale;
};

extern ToySynth toySynth;



#endif //SYNTH_SYNTHESIZER_H
