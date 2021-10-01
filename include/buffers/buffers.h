//
// Created by Michael Skiles on 9/15/21.
//

#ifndef SYNTH_BUFFERS_H
#define SYNTH_BUFFERS_H

#include <inttypes.h>
#include <synthesizer/VoiceList.h>
#include "io/InputSnapshot.h"
#include "toy_defines.h"

extern InputSnapshotBool INPUT_BUFFER_BOOL[INPUT_BUFFER_SIZE_BOOLEAN];
extern InputSnapshotFloat INPUT_BUFFER_FLOAT[INPUT_BUFFER_SIZE_FLOAT];
extern InputSnapshotUint8 INPUT_BUFFER_UINT8[INPUT_BUFFER_SIZE_UINT8];
extern InputSnapshotInt16 INPUT_BUFFER_INT16[INPUT_BUFFER_SIZE_INT16];
extern InputSnapshotBool active_voice;

extern uint8_t voices[MAX_VOICES];
extern VoiceList voiceList;

// LCD
extern lcd_char LCD_DISP_FRONT_BUFFER[LCD_ROWS * LCD_COLS];
extern lcd_char LCD_DISP_BACK_BUFFER[LCD_ROWS * LCD_COLS];
extern lcd_char LCD_LAYOUT_BUFFER_MCP_LOWER[8];
extern lcd_char LCD_LAYOUT_BUFFER_MCP_UPPER[8];


#endif //SYNTH_BUFFERS_H
