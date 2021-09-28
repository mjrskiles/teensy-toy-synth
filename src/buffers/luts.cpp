//
// Created by Michael Skiles on 9/26/21.
//

#include "buffers/luts.h"

uint8_t MCP_INPUT_MASKS[] = {
        0x01, 0x02, 0x04, 0x08,
        0x10, 0x20, 0x40, 0x80
};

const char *input_buffer_bool_names[] = {
        "input_bool_0", "input_bool_1", "input_bool_2", "input_bool_3",
        "input_bool_4", "input_bool_5", "input_bool_6", "input_bool_7",
        "input_bool_8", "input_bool_9", "input_bool_10", "input_bool_11",
        "input_bool_12", "input_bool_13", "input_bool_14", "input_bool_15",
        "input_bool_16", "input_bool_17", "input_bool_18", "input_bool_19",
        "input_bool_20", "input_bool_21", "input_bool_22", "input_bool_23",
        "input_bool_24", "input_bool_25", "input_bool_26", "input_bool_27",
        "input_bool_28", "input_bool_29", "input_bool_30", "input_bool_31",
        "input_bool_32", "input_bool_33", "input_bool_34", "input_bool_35",
        "input_bool_36", "input_bool_37", "input_bool_38", "input_bool_39",
        "input_bool_40", "input_bool_41", "input_bool_42", "input_bool_43",
        "input_bool_44", "input_bool_45", "input_bool_46", "input_bool_47",
        "input_bool_48", "input_bool_49", "input_bool_50", "input_bool_51",
        "input_bool_52", "input_bool_53", "input_bool_54", "input_bool_55",
        "input_bool_56", "input_bool_57", "input_bool_58", "input_bool_59",
        "input_bool_60", "input_bool_61", "input_bool_62", "input_bool_63",
        "input_bool_64", "input_bool_65", "input_bool_66", "input_bool_67",
        "input_bool_68", "input_bool_69", "input_bool_70", "input_bool_71",
        "input_bool_72", "input_bool_73", "input_bool_74", "input_bool_75",
        "input_bool_76", "input_bool_77", "input_bool_78", "input_bool_79",
        "input_bool_80", "input_bool_81", "input_bool_82", "input_bool_83",
        "input_bool_84", "input_bool_85", "input_bool_86", "input_bool_87",
        "input_bool_88", "input_bool_89", "input_bool_90", "input_bool_91",
        "input_bool_92", "input_bool_93", "input_bool_94", "input_bool_95",
        "input_bool_96", "input_bool_97", "input_bool_98", "input_bool_99",
        "input_bool_100", "input_bool_101", "input_bool_102", "input_bool_103",
        "input_bool_104", "input_bool_105", "input_bool_106", "input_bool_107",
        "input_bool_108", "input_bool_109", "input_bool_110", "input_bool_111",
        "input_bool_112", "input_bool_113", "input_bool_114", "input_bool_115",
        "input_bool_116", "input_bool_117", "input_bool_118", "input_bool_119",
        "input_bool_120", "input_bool_121", "input_bool_122", "input_bool_123",
        "input_bool_124", "input_bool_125", "input_bool_126", "input_bool_127",
        "input_bool_128", "input_bool_129", "input_bool_130", "input_bool_131",
        "input_bool_132", "input_bool_133", "input_bool_134", "input_bool_135",
        "input_bool_136", "input_bool_137", "input_bool_138", "input_bool_139",
        "input_bool_140", "input_bool_141", "input_bool_142", "input_bool_143",
        "input_bool_144", "input_bool_145", "input_bool_146", "input_bool_147",
        "input_bool_148", "input_bool_149", "input_bool_150", "input_bool_151",
        "input_bool_152", "input_bool_153", "input_bool_154", "input_bool_155",
        "input_bool_156", "input_bool_157", "input_bool_158", "input_bool_159",
        "input_bool_160", "input_bool_161", "input_bool_162", "input_bool_163",
        "input_bool_164", "input_bool_165", "input_bool_166", "input_bool_167",
        "input_bool_168", "input_bool_169", "input_bool_170", "input_bool_171",
        "input_bool_172", "input_bool_173", "input_bool_174", "input_bool_175",
        "input_bool_176", "input_bool_177", "input_bool_178", "input_bool_179",
        "input_bool_180", "input_bool_181", "input_bool_182", "input_bool_183",
        "input_bool_184", "input_bool_185", "input_bool_186", "input_bool_187",
        "input_bool_188", "input_bool_189", "input_bool_190", "input_bool_191",
        "input_bool_192", "input_bool_193", "input_bool_194", "input_bool_195",
        "input_bool_196", "input_bool_197", "input_bool_198", "input_bool_199",
        "input_bool_200", "input_bool_201", "input_bool_202", "input_bool_203",
        "input_bool_204", "input_bool_205", "input_bool_206", "input_bool_207",
        "input_bool_208", "input_bool_209", "input_bool_210", "input_bool_211",
        "input_bool_212", "input_bool_213", "input_bool_214", "input_bool_215",
        "input_bool_216", "input_bool_217", "input_bool_218", "input_bool_219",
        "input_bool_220", "input_bool_221", "input_bool_222", "input_bool_223",
        "input_bool_224", "input_bool_225", "input_bool_226", "input_bool_227",
        "input_bool_228", "input_bool_229", "input_bool_230", "input_bool_231",
        "input_bool_232", "input_bool_233", "input_bool_234", "input_bool_235",
        "input_bool_236", "input_bool_237", "input_bool_238", "input_bool_239",
        "input_bool_240", "input_bool_241", "input_bool_242", "input_bool_243",
        "input_bool_244", "input_bool_245", "input_bool_246", "input_bool_247",
        "input_bool_248", "input_bool_249", "input_bool_250", "input_bool_251",
        "input_bool_252", "input_bool_253", "input_bool_254", "input_bool_255"
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



static const char scaleNameCMajor[32] = "C Major\0";

// TODO make scales generic
const MidiNotes bms_CMajor[] = {
        MidiNotes::NOTE_C4, MidiNotes::NOTE_D4, MidiNotes::NOTE_E4, MidiNotes::NOTE_F4,
        MidiNotes::NOTE_G4, MidiNotes::NOTE_A4, MidiNotes::NOTE_B4, MidiNotes::NOTE_C5,
        MidiNotes::NOTE_D5, MidiNotes::NOTE_E5, MidiNotes::NOTE_F5, MidiNotes::NOTE_G5,
        MidiNotes::NOTE_A5, MidiNotes::NOTE_B5, MidiNotes::NOTE_C6, MidiNotes::NOTE_D6
};

const MidiNotes BbMajorScale[] = {
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
        3, 2, 1, 0,
        7, 6, 5, 4
};


struct Scale {
    const char *Name;
    MidiNotes ButtonMap[16];
};