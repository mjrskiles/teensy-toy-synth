//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_CALLBACKS_H
#define SYNTH_CALLBACKS_H

#include "Controller.h"
#include <HardwareSerial.h>
#include "MCP23008.h"
#include "buffers/buffers.h"
#include "io/InputSnapshot.h"
#include "VirtualInput.h"
#include "buffers/luts.h"
#include "synthesizer/synthesizer.h"
#include "buffers/buf_utils.h"

MCP23008 mcp_periph1 = MCP23008(0x20);
MCP23008 mcp_kbUpper8 = MCP23008(0x21);
MCP23008 mcp_kbLower8 = MCP23008(0x22);

// TODO move these out of this file
ToySynth toySynth = ToySynth();
/*
 * Lower 8 Pollster cb
 */
void cb_lower8Pollster() {
    keyboard_io_word_previous = keyboard_io_word;

    uint8_t gpio = mcp_kbLower8.readRegister(mcp_kbLower8.getGpio());
    uint16_t keyboard_word_masked = keyboard_io_word & 0xff00;
    keyboard_io_word = keyboard_word_masked | (uint16_t) gpio;
}

void cb_upper8Pollster() {
    keyboard_io_word_previous = keyboard_io_word;

    uint8_t gpio = mcp_kbUpper8.readRegister(mcp_kbUpper8.getGpio());
    uint16_t keyboard_word_masked = keyboard_io_word & 0x00ff;
    uint16_t orWord = gpio << 8;
    keyboard_io_word = keyboard_word_masked | orWord;
}

void cb_peripheralPollster() {
    uint8_t gpio = mcp_periph1.readRegister(mcp_kbUpper8.getGpio());
    Serial.printf("Periph IO word: %x\n", gpio);
}

void cb_mcpInit(MCP23008 mcp) {
    Serial.println("Begin mcp init block");
    Serial.println("constructor");
    mcp.init();
    Serial.println("init");
    delay(100);
    uint8_t iocon = mcp.readRegister(0x05); // check the iocon register
    Serial.println("iocon read");
    Serial.printf("MCP IOCON reg: %hhu\n", iocon);
    uint8_t gppu = mcp.readRegister(0x06);
    Serial.printf("MCP GPPU reg: %hhu\n", gppu);
    Serial.println("End mcp init block");
}

void cb_pollsterInitUpper() {
    cb_mcpInit(mcp_kbUpper8);
}

void cb_pollsterInitLower() {
    cb_mcpInit(mcp_kbLower8);
}

void cb_pollsterInitPeriph() {
    cb_mcpInit(mcp_periph1);
}

/*
 *  Display Layouts
 */
void cb_LayoutMcpLower(lcd_char *buffer) {
    for (int i = 0; i < 8; i++) {
        buffer[i] = INPUT_BUFFER_BOOL[i].asBool() ? '1' : '0'; // TODO need to pass in a proper array index somehow
    }
}

void cb_LayoutMcpUpper(lcd_char *buffer) {
    for (int i = 0; i < 8; i++) {
        buffer[i] = INPUT_BUFFER_BOOL[i + 8].asBool() ? '1' : '0'; // TODO need to pass in a proper array index somehow
    }
}

void cb_LayoutCurrentNoteName(lcd_char *buffer) {
    int i = active_voice->getFromIndex();
    uint8_t logicalLoc = physical_to_logical_button_loc[i];
    uint8_t scaleLoc = currentScale[logicalLoc];
    const lcd_char *namePointer = midi_note_names[scaleLoc];
//    Serial.println("writing to temp note name buffer...");
    for (int j = 0; j < LCD_NOTE_NAME_CHAR_WIDTH; j++) {
        buffer[j] = namePointer[j];
    }
//    Serial.print((const char *) buffer);
}

#endif //SYNTH_CALLBACKS_H
