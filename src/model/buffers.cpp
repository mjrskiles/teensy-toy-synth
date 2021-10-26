//
// Created by Michael Skiles on 9/21/21.
//

#include "model/buffers.h"

uint16_t keyboard_io_word = 0;
uint16_t keyboard_io_word_previous = 0;
MidiNote activeNote = NOTE_AMINUS1;
int attackValueRaw;
int decayValueRaw;
int sustainValueRaw;
int releaseValueRaw;
float knobVolumeScaled;

char attackStr[5]; // m
char decayStr[5];
char sustainStr[5];
char releaseStr[5];

uint8_t bankSelectByte = 0;

float analog_control_1 = 0.0;
float analog_control_2 = 0.0;
float analog_control_3 = 0.0;
float analog_control_4 = 0.0;

lcd_char LCD_DISP_FRONT_BUFFER[LCD_ROWS * LCD_COLS] {
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' '
};

lcd_char LCD_DISP_BACK_BUFFER[LCD_ROWS * LCD_COLS] {
    ' ',' ',' ',' ', ' ',' ',' ',' ', ' ',' ',' ',' ', ' ',' ',' ',' ',
    ' ',' ',' ',' ', ' ',' ',' ',' ', ' ',' ',' ',' ', ' ',' ',' ',' '
};

lcd_char LCD_LAYOUT_BUFFER_MCP_LOWER[8];
lcd_char LCD_LAYOUT_BUFFER_MCP_UPPER[8];
lcd_char LCD_LAYOUT_BUFFER_NOTE_NAME[LCD_NOTE_NAME_CHAR_WIDTH + 1] {'n','o','n','e','\0'};

lcd_char LCD_LAYOUT_TEST1[16];
lcd_char LCD_LAYOUT_TEST2[16];

lcd_char LCD_LAYOUT_ATTACK[7];
lcd_char LCD_LAYOUT_DECAY[7];
lcd_char LCD_LAYOUT_SUSTAIN[7];
lcd_char LCD_LAYOUT_RELEASE[7];

VoiceState vs0(&pwm1, &pwm_env1, 0, NOTE_A4, false);
VoiceState vs1(&pwm2, &pwm_env2, 0, NOTE_CS5, false);
VoiceState vs2(&pwm3, &pwm_env3, 0, NOTE_E5, false);
VoiceState vs3(&pwm4, &pwm_env4, 0, NOTE_GS5, false);
VoiceState vsa[] {vs0, vs1, vs2, vs3};