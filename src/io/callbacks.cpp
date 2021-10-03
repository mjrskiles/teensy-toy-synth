//
// Created by mjrsk on 10/2/2021.
//
#include "io/callbacks.h"

MCP23008 mcp_periph1 = MCP23008(0x20);
MCP23008 mcp_kbUpper8 = MCP23008(0x21);
MCP23008 mcp_kbLower8 = MCP23008(0x22);

/*
 * Callback for the listener to use
 */
void cb_noteButtonListener(InputSnapshot &snapshot) {
    Serial.printf("Snapshot | %s\n", snapshot.name());
    Serial.printf("  val: %s\n", snapshot.asBool() ? "true" : "false");
    Serial.printf("  time: %lu\n", snapshot.time());
    uint8_t but = mcp_to_physical_button_map[snapshot.getFromIndex()];
    MidiNotes scaleNote =BbMajorScale[but];
    float freq = midi_frequencies[scaleNote];
    squarewaveBase.frequency(freq);
    if (snapshot.asBool()) {
        envelope2.noteOn();
        squarewaveBase.amplitude(1.0);
        active_voice = &snapshot;
    } else if (!isAnyKeyboardKeyPressed()) {
        squarewaveBase.amplitude(0.0);
        envelope2.noteOff();
        Serial.println("Env2 Off");
    }
}

void cb_periphLogListener(InputSnapshot &snapshot) {
    Serial.printf("Snapshot | %s\n", snapshot.name());
    Serial.printf("  val: %s\n", snapshot.asBool() ? "true" : "false");
    Serial.printf("  time: %lu\n", snapshot.time());
}

void cb_processGpio(uint8_t gpioWord, VirtualInput *inputs, uint8_t size) {
    for (int i = 0; i < size; i++) {
        int index = inputs[i].getIndex();
        uint8_t onInputWord = gpioWord & MCP_INPUT_MASKS[i];
        bool previousState = INPUT_BUFFER_BOOL[index].asBool(); // Get the buffer state before we change it

        if (onInputWord) {
            INPUT_BUFFER_BOOL[index].setTime(millis());
            INPUT_BUFFER_BOOL[index].setState(true);
            if (!previousState) {
                inputs[i].notifyChangeListeners();
            }
        } else {
            INPUT_BUFFER_BOOL[index].setTime(millis());
            INPUT_BUFFER_BOOL[index].setState(false);
            if (previousState){
                inputs[i].notifyChangeListeners();
            }
        }
    }
}

/*
 * Lower 8 Pollster cb
 */
void cb_lower8Pollster(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_kbLower8.readRegister(mcp_kbLower8.getGpio());
    cb_processGpio(gpio, inputs, size);

}

void cb_upper8Pollster(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_kbUpper8.readRegister(mcp_kbUpper8.getGpio());
    cb_processGpio(gpio, inputs, size);
}

void cb_peripheralPollster(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_periph1.readRegister(mcp_kbUpper8.getGpio());
    cb_processGpio(gpio, inputs, size);
}

/*
 * Callback for the pollster, uses the MCP23008 to get the button state
 */
void note0PollsterCallback() {
    uint8_t gpio = mcp_kbUpper8.readRegister(0x09); // check the io register
    // check  if note 0 is active
    Serial.println("pollster _callback:");
    Serial.printf(" value: %x\n", gpio);
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
    Serial.print((const char *) buffer);
}