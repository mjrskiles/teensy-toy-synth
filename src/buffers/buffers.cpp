//
// Created by Michael Skiles on 9/21/21.
//

#include <io/InputSnapshot.h>
#include <toy_defines.h>
#include <synthesizer/VoiceList.h>

uint16_t keyboard_io_word = 0;

InputSnapshotBool INPUT_BUFFER_BOOL[INPUT_BUFFER_SIZE_BOOLEAN];
InputSnapshotFloat INPUT_BUFFER_FLOAT[INPUT_BUFFER_SIZE_FLOAT];
InputSnapshotUint8 INPUT_BUFFER_UINT8[INPUT_BUFFER_SIZE_UINT8];
InputSnapshotInt16 INPUT_BUFFER_INT16[INPUT_BUFFER_SIZE_INT16];

InputSnapshot *active_voice = &INPUT_BUFFER_BOOL[0];
uint8_t voices[MAX_VOICES];
VoiceList voiceList = VoiceList();

uint8_t LCD_DISP_FRONT_BUFFER[LCD_ROWS * LCD_COLS] {
    ' ','t',' ','o',' ','y',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' ',
    ' ','s','y','n','t','h',' ',' ',' ',' ',' ',' ', ' ',' ',' ',' '
};

uint8_t LCD_DISP_BACK_BUFFER[LCD_ROWS * LCD_COLS] {
    ' ',' ',' ',' ', ' ',' ',' ',' ', ' ',' ',' ',' ', ' ',' ',' ',' ',
    ' ',' ',' ',' ', ' ',' ',' ',' ', ' ',' ',' ',' ', ' ',' ',' ',' '
};

lcd_char LCD_LAYOUT_BUFFER_MCP_LOWER[8];
lcd_char LCD_LAYOUT_BUFFER_MCP_UPPER[8];
lcd_char LCD_LAYOUT_BUFFER_NOTE_NAME[LCD_NOTE_NAME_CHAR_WIDTH + 1] {'n','o','n','e','\0'};

const char* INPUT_NAMES_BOOL[] = {
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