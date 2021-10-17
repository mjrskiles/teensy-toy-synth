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

uint8_t gpio_lower_previous = 0;
uint8_t gpio_upper_previous = 0;


/*
 * Lower 8 Pollster cb
 */
void cb_lower8Pollster() {
    keyboard_io_word_previous = keyboard_io_word;
    uint8_t gpio;
    noInterrupts()
    // The reason for this do while loop is to prevent note sticking due to button bounce.
    // It seems that sometimes this function would get triggered due to a legitimate state change
    // but the MCP would read an erroneous value, which had changed between the interrupt and code execution.
    do {
        gpio = mcp_kbLower8.readRegister(mcp_kbLower8.getGpio());
        keyboard_io_word &= 0xff00; // zero out the word to take in the new data
        keyboard_io_word |= gpio;
    } while (gpio && gpio == gpio_lower_previous); // This function should only be called on change of state
    interrupts();
    gpio_lower_previous = gpio;
    toySynth.notify();
}

void cb_upper8Pollster() {
    keyboard_io_word_previous = keyboard_io_word;
    uint8_t gpio;
    noInterrupts();
    do {
        gpio = mcp_kbUpper8.readRegister(mcp_kbUpper8.getGpio());
        keyboard_io_word &= 0x00ff;
        keyboard_io_word |= gpio << 8;
    } while (gpio && gpio == gpio_upper_previous);
    interrupts();
    gpio_upper_previous = gpio;
    toySynth.notify();
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
// Digital IO page
void cb_LayoutMcpLower(lcd_char *buffer) {
    for (int i = 0; i < 8; i++) {
        buffer[i] = isOneAtIndex(keyboard_io_word, i) ? '1' : '0'; // TODO need to pass in a proper array index somehow
    }
}

void cb_LayoutMcpUpper(lcd_char *buffer) {
    for (int i = 0; i < 8; i++) {
        buffer[i] = isOneAtIndex(keyboard_io_word, i + 8) ? '1' : '0'; // TODO need to pass in a proper array index somehow
    }
}

void cb_LayoutCurrentNoteName(lcd_char *buffer) {
    const lcd_char *namePointer = midi_note_names[activeNote];
    for (int j = 0; j < LCD_NOTE_NAME_CHAR_WIDTH; j++) {
        buffer[j] = namePointer[j];
    }
//    Serial.print((const char *) buffer);
}

// Page 2
void cb_LayoutTest1(lcd_char *buffer) {
    const lcd_char *test = "Test String";
    for (int i = 0; i < 11; i++) {
        buffer[i] = test[i];
    }
}


// Page 3
void cb_LayoutTest2(lcd_char *buffer) {
    const char *test = "--Test Str2--";
    for (int i = 0; i < 13; i++) {
        buffer[i] = test[i];
    }
}

#endif //SYNTH_CALLBACKS_H
