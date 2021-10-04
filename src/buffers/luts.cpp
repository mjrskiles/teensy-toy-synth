//
// Created by Michael Skiles on 9/26/21.
//


#include "buffers/luts.h"


/*
 * Corresponds to physical layout
 * 12, 13, 14, 15
 * 8, 9, 10, 11
 * 4, 5, 6, 7
 * 0, 1, 2, 3
 */
uint8_t physical_to_logical_button_loc[16] {
    7, 6, 5, 4,
    3, 2, 1, 0,
    15, 14, 13, 12,
    11, 10, 9, 8
};



uint8_t MCP_INPUT_MASKS[] = {
        0x01, 0x02, 0x04, 0x08,
        0x10, 0x20, 0x40, 0x80
};

float midi_frequencies[] = {
        8.176,8.662,9.177,9.723,
        10.301,10.913,11.562,12.250,
        12.978,13.750,14.568,15.434,
        16.352,17.324,18.354,19.445,
        20.601,21.826,23.124,24.499,
        25.956,27.500,29.135,30.867,
        32.703,34.648,36.708,38.890,
        41.203,43.653,46.249,48.999,
        51.913,55.000,58.270,61.735,
        65.406,69.295,73.416,77.781,
        82.406,87.307,92.499,97.998,
        103.82,110.00,116.54,123.47,
        130.81,138.59,146.83,155.56,
        164.81,174.61,184.99,195.99,
        207.65,220.00,233.08,246.94,
        261.63,277.18,293.66,311.13,
        329.63,349.23,369.99,391.99,
        415.31,440.00,466.16,493.88,
        523.25,554.37,587.33,622.25,
        659.26,698.46,739.99,783.99,
        830.61,880.00,932.32,987.77,
        1046.5,1108.7,1174.7,1244.5,
        1318.5,1396.9,1480.0,1568.0,
        1661.2,1760.0,1864.7,1975.5,
        2093.0,2217.5,2349.3,2489.0,
        2637.0,2793.8,2960.0,3136.0,
        3322.4,3520.0,3729.3,3951.1,
        4186.0,4434.9,4698.6,4978.0,
        5274.0,5587.7,5919.9,6271.9,
        6644.9,7040.0,7458.6,7902.1,
        8372.0,8869.8,9397.3,9956.1,
        10548.1,11175.3,11839.8,12543.9,
        };

const lcd_char* midi_note_names[] {
    "C -1\0", "C#-1\0", "D -1\0", "D#-1\0",
    "E -1\0", "F -1\0", "F#-1\0", "G -1\0",
    "G#-1\0", "A -1\0", "Bb-1\0", "B -1\0",
    "C  0\0", "C# 0\0", "D  0\0", "D#-1\0",
    "E  0\0", "F  0\0", "F# 0\0", "G  0\0",
    "G# 0\0", "A  0\0", "Bb 0\0", "B  0\0",
    "C  1\0", "C# 1\0", "D  1\0", "D# 1\0",
    "E  1\0", "F  1\0", "F# 1\0", "G  1\0",
    "G# 1\0", "A  1\0", "Bb 1\0", "B  1\0",
    "C  2\0", "C# 2\0", "D  2\0", "D# 2\0",
    "E  2\0", "F  2\0", "F# 2\0", "G  2\0",
    "G# 2\0", "A  2\0", "Bb 2\0", "B  2\0",
    "C  3\0", "C# 3\0", "D  3\0", "D# 3\0",
    "E  3\0", "F  3\0", "F# 3\0", "G  3\0",
    "G# 3\0", "A  3\0", "Bb 3\0", "B  3\0",
    "C  4\0", "C# 4\0", "D  4\0", "D# 4\0",
    "E  4\0", "F  4\0", "F# 4\0", "G  4\0",
    "G# 4\0", "A  4\0", "Bb 4\0", "B  4\0",
    "C  5\0", "C# 5\0", "D  5\0", "D# 5\0",
    "E  5\0", "F  5\0", "F# 5\0", "G  5\0",
    "G# 5\0", "A  5\0", "Bb 5\0", "B  5\0",
    "C  6\0", "C# 6\0", "D  6\0", "D# 6\0",
    "E  6\0", "F  6\0", "F# 6\0", "G  6\0",
    "G# 6\0", "A  6\0", "Bb 6\0", "B  6\0",
    "C  7\0", "C# 7\0", "D  7\0", "D# 7\0",
    "E  7\0", "F  7\0", "F# 7\0", "G  7\0",
    "G# 7\0", "A  7\0", "Bb 7\0", "B  7\0",
    "C  8\0", "C# 8\0", "D  8\0", "D# 8\0",
    "E  8\0", "F  8\0", "F# 8\0", "G  8\0",
    "G# 8\0", "A  8\0", "Bb 8\0", "B  8\0",
    "C  9\0", "C# 9\0", "D  9\0", "D# 9\0",
    "E  9\0", "F  9\0", "F# 9\0", "G  9\0"
};

static const char scaleNameCMajor[32] = "C Major\0";

// TODO make scales generic
const MidiNotes bms_CMajor[] = {
        MidiNotes::NOTE_C4, MidiNotes::NOTE_D4, MidiNotes::NOTE_E4, MidiNotes::NOTE_F4,
        MidiNotes::NOTE_G4, MidiNotes::NOTE_A4, MidiNotes::NOTE_B4, MidiNotes::NOTE_C5,
        MidiNotes::NOTE_D5, MidiNotes::NOTE_E5, MidiNotes::NOTE_F5, MidiNotes::NOTE_G5,
        MidiNotes::NOTE_A5, MidiNotes::NOTE_B5, MidiNotes::NOTE_C6, MidiNotes::NOTE_D6
};

MidiNotes BbMajorScale[] = {
        MidiNotes::NOTE_AS3, NOTE_C4, NOTE_D4, NOTE_DS4,
        NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4,
        NOTE_C5, NOTE_D5, NOTE_DS5, NOTE_F5,
        NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_C6
};

/*
 *  Physical button layout for main keypad
 *  |  3 |  2 |  1 |  0 | <- MCP UPPER
 *  |  7 |  6 |  5 |  4 |
 *  |  3 |  2 |  1 |  0 | <- MCP LOWER
 *  |  7 |  6 |  5 |  4 |
 */
const uint8_t mcp_to_physical_button_map[] = {
        7, 6, 5, 4,
        3, 2, 1, 0,
        15, 14, 13, 12,
        11, 10, 9, 8
};

struct Scale {
    const char *Name;
    MidiNotes ButtonMap[16];
};

// TODO lookup the current note from the current scale
MidiNotes *currentScale = BbMajorScale;