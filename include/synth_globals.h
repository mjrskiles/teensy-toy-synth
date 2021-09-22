//
// Created by Michael Skiles on 9/15/21.
//

#ifndef SYNTH_SYNTH_GLOBALS_H
#define SYNTH_SYNTH_GLOBALS_H

#include <inttypes.h>
#include "io/InputSnapshot.h"
#include "synth_defines.h"

InputSnapshotBool INPUT_BUFFER_BOOL[INPUT_BUFFER_SIZE_BOOLEAN];
InputSnapshotFloat INPUT_BUFFER_FLOAT[INPUT_BUFFER_SIZE_FLOAT];
InputSnapshotUint8 INPUT_BUFFER_UINT8[INPUT_BUFFER_SIZE_UINT8];
InputSnapshotInt16 INPUT_BUFFER_INT16[INPUT_BUFFER_SIZE_INT16];

#endif //SYNTH_SYNTH_GLOBALS_H
