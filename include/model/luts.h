//
// Created by Michael Skiles on 8/12/21.
//

#ifndef SYNTH_LUTS_H
#define SYNTH_LUTS_H

#include <inttypes.h>
#include <toy_types.h>

extern const uint8_t physical_to_logical_button_loc[16];

enum MidiNote : int {
    NOTE_CMINUS1 , NOTE_CSMINUS1, NOTE_DMINUS1 , NOTE_DSMINUS1,
    NOTE_EMINUS1 , NOTE_FMINUS1 , NOTE_FSMINUS1, NOTE_GMINUS1 ,
    NOTE_GSMINUS1, NOTE_AMINUS1 , NOTE_ASMINUS1, NOTE_BMINUS1 ,
    NOTE_C0 ,NOTE_CS0,NOTE_D0 ,NOTE_DS0,
    NOTE_E0 ,NOTE_F0 ,NOTE_FS0,NOTE_G0 ,
    NOTE_GS0,NOTE_A0 ,NOTE_AS0,NOTE_B0 ,
    NOTE_C1 ,NOTE_CS1,NOTE_D1 ,NOTE_DS1,
    NOTE_E1 ,NOTE_F1 ,NOTE_FS1,NOTE_G1 ,
    NOTE_GS1,NOTE_A1 ,NOTE_AS1,NOTE_B1 ,
    NOTE_C2 ,NOTE_CS2,NOTE_D2 ,NOTE_DS2,
    NOTE_E2 ,NOTE_F2 ,NOTE_FS2,NOTE_G2 ,
    NOTE_GS2,NOTE_A2 ,NOTE_AS2,NOTE_B2 ,
    NOTE_C3 ,NOTE_CS3,NOTE_D3 ,NOTE_DS3,
    NOTE_E3 ,NOTE_F3 ,NOTE_FS3,NOTE_G3 ,
    NOTE_GS3,NOTE_A3 ,NOTE_AS3,NOTE_B3 ,
    NOTE_C4 ,NOTE_CS4,NOTE_D4 ,NOTE_DS4,
    NOTE_E4 ,NOTE_F4 ,NOTE_FS4,NOTE_G4 ,
    NOTE_GS4,NOTE_A4 ,NOTE_AS4,NOTE_B4 ,
    NOTE_C5 ,NOTE_CS5,NOTE_D5 ,NOTE_DS5,
    NOTE_E5 ,NOTE_F5 ,NOTE_FS5,NOTE_G5 ,
    NOTE_GS5,NOTE_A5 ,NOTE_AS5,NOTE_B5 ,
    NOTE_C6 ,NOTE_CS6,NOTE_D6 ,NOTE_DS6,
    NOTE_E6 ,NOTE_F6 ,NOTE_FS6,NOTE_G6 ,
    NOTE_GS6,NOTE_A6 ,NOTE_AS6,NOTE_B6 ,
    NOTE_C7 ,NOTE_CS7,NOTE_D7 ,NOTE_DS7,
    NOTE_E7 ,NOTE_F7 ,NOTE_FS7,NOTE_G7 ,
    NOTE_GS7,NOTE_A7 ,NOTE_AS7,NOTE_B7 ,
    NOTE_C8 ,NOTE_CS8,NOTE_D8 ,NOTE_DS8,
    NOTE_E8 ,NOTE_F8 ,NOTE_FS8,NOTE_G8 ,
    NOTE_GS8,NOTE_A8 ,NOTE_AS8,NOTE_B8 ,
    NOTE_C9 ,NOTE_CS9,NOTE_D9 ,NOTE_DS9,
    NOTE_E9 ,NOTE_F9 ,NOTE_FS9,NOTE_G9
};

extern const lcd_char* midi_note_names[128];

extern uint8_t MCP_INPUT_MASKS[8];
extern float midi_frequencies[128];
extern const char *input_buffer_bool_names[256];
extern const uint8_t mcp_to_physical_button_map[16];



// Scales
struct Scale {
    const char *name;
    MidiNote notes[16];
};


// bms - button mapped scale
extern MidiNote bms_CMajor[16];
extern MidiNote bms_BbMajor[16];
extern MidiNote bms_BbChromatic[16];

extern MidiNote *currentScale;

#endif //SYNTH_LUTS_H
