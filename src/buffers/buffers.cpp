//
// Created by Michael Skiles on 9/21/21.
//

#include <io/InputSnapshot.h>
#include <synth_defines.h>
#include <io/VirtualInput.h>

InputSnapshotBool INPUT_BUFFER_BOOL[INPUT_BUFFER_SIZE_BOOLEAN];
InputSnapshotFloat INPUT_BUFFER_FLOAT[INPUT_BUFFER_SIZE_FLOAT];
InputSnapshotUint8 INPUT_BUFFER_UINT8[INPUT_BUFFER_SIZE_UINT8];
InputSnapshotInt16 INPUT_BUFFER_INT16[INPUT_BUFFER_SIZE_INT16];

extern InputSnapshotBool ACTIVE_VOICES[8];

uint8_t num_active_voices() {
    uint8_t numActive = 0;
    for (int i = 0; i < 8; i++) {
        if (ACTIVE_VOICES[i].asBool()){
            numActive++;
        }
    }
    return numActive;
}