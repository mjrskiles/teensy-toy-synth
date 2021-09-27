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

MCP23008 mcp_periph1 = MCP23008(0x20);
MCP23008 mcp_kbUpper8 = MCP23008(0x21);
MCP23008 mcp_kbLower8 = MCP23008(0x22);

/*
 * Callback for the listener to use
 */
void noteButtonListenerCallback(InputSnapshot &snapshot) {
    Serial.printf("Snapshot | %s\n", snapshot.name());
    Serial.printf("  val: %s\n", snapshot.asBool() ? "true" : "false");
    Serial.printf("  time: %lu\n", snapshot.time());
    // TODO this is garbo, I haven't even written it yet but it needs to be genericized and stuff. jUst to test turning on
    // voices from a callback. Can't use the index directly in the future. Need a map from VI index to virtual keyboard layout
    MidiNotes scaleNote = BbMajorScale[snapshot.getFromIndex()];
    squarewaveBase.frequency(midi_frequencies[scaleNote]);
    squarewaveBase.amplitude(snapshot.asBool() ? 1.0 : 0.0);
}

/*
 * Lower 8 Pollster cb
 */
void lower8PollsterCallback(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_kbLower8.readRegister(mcp_kbLower8.getGpio());
//    Serial.println("-Lower 8 Pollster-");
//    Serial.printf("gpio: %x\n", gpio);
//    Serial.println("Lower pollster end");
}

void upper8PollsterCallback(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_kbUpper8.readRegister(mcp_kbUpper8.getGpio());

    for (int i = 0; i < size; i++) {
        int index = inputs[i].getIndex();
        uint8_t onInputWord = gpio & MCP_INPUT_MASKS[i];
        if (onInputWord) {
            INPUT_BUFFER_BOOL[index].setTime(millis());
            INPUT_BUFFER_BOOL[index].setState(true);
            inputs[i].notifyChangeListeners();
        } else if (INPUT_BUFFER_BOOL[index].asBool()) {
            INPUT_BUFFER_BOOL[index].setTime(millis());
            INPUT_BUFFER_BOOL[index].setState(false);
            inputs[i].notifyChangeListeners();
        }
    }
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

void pollsterInitUpper() {
    Serial.println("Begin mcp init block");
    Serial.println("constructor");
    mcp_kbUpper8.init();
    Serial.println("init");
    delay(100);
    uint8_t iocon = mcp_kbUpper8.readRegister(0x05); // check the iocon register
    Serial.println("iocon read");
    Serial.printf("MCP IOCON reg: %hhu\n", iocon);
    uint8_t gppu = mcp_kbUpper8.readRegister(0x06);
    Serial.printf("MCP GPPU reg: %hhu\n", gppu);
    Serial.println("End mcp init block");
}

void pollsterInitLower() {
    Serial.println("Begin mcp init block");
    Serial.println("constructor");
    mcp_kbLower8.init();
    Serial.println("init");
    delay(100);
    uint8_t iocon = mcp_kbLower8.readRegister(0x05); // check the iocon register
    Serial.println("iocon read");
    Serial.printf("MCP IOCON reg: %hhu\n", iocon);
    uint8_t gppu = mcp_kbLower8.readRegister(0x06);
    Serial.printf("MCP GPPU reg: %hhu\n", gppu);
    Serial.println("End mcp init block");
}

/***************************
 * Note button listeners
 */
void logCallback(InputSnapshot &snapshot) {
    Serial.printf("Logback from %s\n", snapshot.name());
    Serial.printf("Payload: ");
    switch (snapshot.type()) {
        case BOOL:
            Serial.printf("%s", (bool) (snapshot.asBool()) ? "true" : "false");
        case FLOAT:
            Serial.printf("%d", (int)snapshot.asFloat());
//        case CONTINUOUS_FLOAT:
//            Serial.printf("%0.2f", (float)*(snapshot.data));
        default:
            Serial.println("???");
    }
    Serial.printf("\n--\n");

}


void eric_holder() {
    // Button select changes the waveform type
    if (false) {
        Serial.println("Log Button");
        Serial.println("Control  | Value");
//        Serial.printf( "Knob 1     %.2f\n", knob_A1);
//        Serial.printf( "Knob 2     %.2f\n", knob_A2);
//        Serial.printf( "Knob 3     %.2f\n", knob_A3);
//        logPrintoutMillisSince = 0;
    }
}

#endif //SYNTH_CALLBACKS_H
