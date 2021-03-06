//
// Created by Michael Skiles on 9/22/21.
//

#ifndef SYNTH_SYNTH_DEFINES_H
#define SYNTH_SYNTH_DEFINES_H

#define MAX_LISTENERS_PER_INPUT (uint8_t)4
#define MAX_INPUTS_PER_POLLSTER (uint8_t)8
#define MAX_POLLSTERS (uint8_t)24

#define INPUT_BUFFER_SIZE_BOOLEAN 256
#define INPUT_BUFFER_SIZE_FLOAT 256
#define INPUT_BUFFER_SIZE_UINT8 256
#define INPUT_BUFFER_SIZE_INT16 256

#define LCD_ROWS 2
#define LCD_COLS 16
#define LCD_LINE_2_START_POS 64
#define LCD_LINE_1_START_POS 0
#define LCD_UPDATE_HZ 12
#define LCD_NOTE_NAME_CHAR_WIDTH 4

#endif //SYNTH_SYNTH_DEFINES_H
