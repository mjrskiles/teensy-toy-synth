//
// Created by Michael Skiles on 9/15/21.
//

#ifndef SYNTH_BUFFERS_H
#define SYNTH_BUFFERS_H

#include <inttypes.h>
#include <synthesizer/pwm_synth.h>
#include "toy_defines.h"
#include "luts.h"

extern uint16_t keyboard_io_word;
extern uint16_t keyboard_io_word_previous;
extern MidiNote activeNote;
extern int attackValueRaw;
extern int decayValueRaw;
extern int sustainValueRaw;
extern int releaseValueRaw;
extern float knobVolumeScaled;

extern char attackStr[5]; // max value will be 1023
extern char decayStr[5];
extern char sustainStr[5];
extern char releaseStr[5];

// LCD
extern lcd_char LCD_DISP_FRONT_BUFFER[LCD_ROWS * LCD_COLS];
extern lcd_char LCD_DISP_BACK_BUFFER[LCD_ROWS * LCD_COLS];
extern lcd_char LCD_LAYOUT_BUFFER_MCP_LOWER[8];
extern lcd_char LCD_LAYOUT_BUFFER_MCP_UPPER[8];
extern lcd_char LCD_LAYOUT_BUFFER_NOTE_NAME[LCD_NOTE_NAME_CHAR_WIDTH + 1]; // 4

// page 2
extern lcd_char LCD_LAYOUT_TEST1[16];
extern lcd_char LCD_LAYOUT_TEST2[16];


extern lcd_char LCD_LAYOUT_ATTACK[7];
extern lcd_char LCD_LAYOUT_DECAY[7];
extern lcd_char LCD_LAYOUT_SUSTAIN[7];
extern lcd_char LCD_LAYOUT_RELEASE[7];

extern VoiceState vs0;
extern VoiceState vs1;
extern VoiceState vs2;
extern VoiceState vs3;
extern VoiceState vsa[];




#endif //SYNTH_BUFFERS_H
