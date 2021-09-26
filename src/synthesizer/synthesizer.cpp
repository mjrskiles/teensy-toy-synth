//
// Created by Michael Skiles on 9/16/21.
//

#include "synthesizer/synthesizer.h"
#include "synth_defines.h"
#include "io/buffers.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       squarewaveBase;      //xy=90,59
AudioSynthWaveformSine   phaseCtrl1;          //xy=99,237
AudioSynthWaveformModulated triwaveBase;   //xy=260,303
AudioEffectEnvelope      envelope2;      //xy=294,119
AudioEffectEnvelope      envelope1;      //xy=381,396
AudioMixer4              mixerEnv1;         //xy=482,113
AudioMixer4              mixerEnv2;         //xy=482,293
AudioMixer4              oscCombineMixer;         //xy=613,187
AudioSynthWaveformSine   lpfCtrl;          //xy=645,300
AudioFilterStateVariable lpf1;        //xy=781,191
AudioMixer4              mixer1;         //xy=984,193
AudioOutputI2S           i2s1;           //xy=1149,189
AudioConnection          patchCord1(squarewaveBase, envelope2);
AudioConnection          patchCord2(squarewaveBase, 0, mixerEnv1, 0);
AudioConnection          patchCord3(phaseCtrl1, 0, triwaveBase, 0);
AudioConnection          patchCord4(triwaveBase, envelope1);
AudioConnection          patchCord5(triwaveBase, 0, mixerEnv2, 0);
AudioConnection          patchCord6(envelope2, 0, mixerEnv1, 1);
AudioConnection          patchCord7(envelope1, 0, mixerEnv2, 1);
AudioConnection          patchCord8(mixerEnv1, 0, oscCombineMixer, 0);
AudioConnection          patchCord9(mixerEnv2, 0, oscCombineMixer, 1);
AudioConnection          patchCord10(oscCombineMixer, 0, lpf1, 0);
AudioConnection          patchCord11(lpfCtrl, 0, lpf1, 1);
AudioConnection          patchCord12(lpf1, 0, mixer1, 0);
AudioConnection          patchCord13(mixer1, 0, i2s1, 0);
AudioConnection          patchCord14(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=585,481
//// GUItool: end automatically generated code

const char *mcpLower8Name = "MCP23008: Lower";
const char *mcpUpper8Name = "MCP23008: Upper";
const char *mcpPeriphName = "MCP23008: Peripheral";

void synth_init() {

    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
    AudioMemory(24);

    // Comment these out if not using the audio adaptor board.
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);

    // Configure for middle C note without modulation
    squarewaveBase.begin(WAVEFORM_SQUARE);
    triwaveBase.begin(WAVEFORM_TRIANGLE);

    for (int i = 0; i < INPUT_BUFFER_SIZE_BOOLEAN; i++) {
        INPUT_BUFFER_BOOL[i].setName(m)
        // initialize the buffer to a 0 state
    }
}
