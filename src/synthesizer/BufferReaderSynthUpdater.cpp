//
// Created by Michael Skiles on 9/22/21.
//

#include "synthesizer/BufferReaderSynthUpdater.h"


//void updateInputsFromBuffer() {
//
//
//    uint16_t buttonStateWordLast = buttonWordBuffer;
//    buttonWordBuffer = 0;
//    for (int i = 0; i < 15; i++) {
//        InputSnapshotBool snapshot = INPUT_BUFFER_BOOL[i];
//        buttonWordBuffer |= snapshot.asUint8() << i;
//    }//TODO no magic numbers, this is for testing
//    if (buttonStateWordLast != buttonWordBuffer) {
//        Serial.printf("Input buffer: %x", buttonWordBuffer);
//    }
//
//}
