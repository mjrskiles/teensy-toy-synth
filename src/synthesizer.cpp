//
// Created by Michael Skiles on 9/16/21.
//

#include "synthesizer/synthesizer.h"
#include "synthesizer/components.h

void synth_init() {
    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
    AudioMemory(24);

    // Comment these out if not using the audio adaptor board.
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);

    // Configure for middle C note without modulation
    squarewaveBase.begin(WAVEFORM_SQUARE);
    squarewavePhaseMod.begin(WAVEFORM_SQUARE);
    squarewavePhaseMod.phaseModulation(360.0f);
    phaseCtrl1.frequency(500.0f);
    lpfCtrl.frequency(20000.0f);
}
