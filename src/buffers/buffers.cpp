//
// Created by Michael Skiles on 9/21/21.
//

#include <io/InputSnapshot.h>
#include <synth_defines.h>
#include <io/VirtualInput.h>
#include <synthesizer/VoiceList.h>

InputSnapshotBool INPUT_BUFFER_BOOL[INPUT_BUFFER_SIZE_BOOLEAN];
InputSnapshotFloat INPUT_BUFFER_FLOAT[INPUT_BUFFER_SIZE_FLOAT];
InputSnapshotUint8 INPUT_BUFFER_UINT8[INPUT_BUFFER_SIZE_UINT8];
InputSnapshotInt16 INPUT_BUFFER_INT16[INPUT_BUFFER_SIZE_INT16];

InputSnapshotBool active_voice = InputSnapshotBool();
uint8_t voices[MAX_VOICES];
VoiceList voiceList = VoiceList();