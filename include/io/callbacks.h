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
    uint8_t but = mcp_to_physical_button_map[snapshot.getFromIndex()];
    MidiNotes scaleNote = BbMajorScale[but];
    float freq = midi_frequencies[scaleNote];
    squarewaveBase.frequency(freq);
    squarewaveBase.amplitude(snapshot.asBool() ? 1.0 : 0.0);
    if (snapshot.asBool()) {
        envelope2.noteOn();

    } else if (!snapshot.asBool() && (&snapshot == &active_voice)) {
        envelope2.noteOff();
        Serial.println("Env2 Off");
    }
}

void periphLogListenerCallback(InputSnapshot &snapshot) {
    Serial.printf("Snapshot | %s\n", snapshot.name());
    Serial.printf("  val: %s\n", snapshot.asBool() ? "true" : "false");
    Serial.printf("  time: %lu\n", snapshot.time());
}

void processGpio(uint8_t gpioWord, VirtualInput *inputs, uint8_t size) {
    for (int i = 0; i < size; i++) {
        int index = inputs[i].getIndex();
        uint8_t onInputWord = gpioWord & MCP_INPUT_MASKS[i];
        bool previousState = INPUT_BUFFER_BOOL[index].asBool(); // Get the buffer state before we change it

        if (onInputWord) {
            INPUT_BUFFER_BOOL[index].setTime(millis());
            INPUT_BUFFER_BOOL[index].setState(true);
            if (!previousState) {
                voiceList.addVoice(index);
                inputs[i].notifyChangeListeners();
            }
        } else {
            INPUT_BUFFER_BOOL[index].setTime(millis());
            INPUT_BUFFER_BOOL[index].setState(false);
            if (previousState){
                voiceList.removeVoice(index);
                inputs[i].notifyChangeListeners();
            }
        }
    }
}

/*
 * Lower 8 Pollster cb
 */
void lower8PollsterCallback(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_kbLower8.readRegister(mcp_kbLower8.getGpio());
    processGpio(gpio, inputs, size);

}

void upper8PollsterCallback(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_kbUpper8.readRegister(mcp_kbUpper8.getGpio());
    processGpio(gpio, inputs, size);
}

void peripheralPollsterCallback(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_periph1.readRegister(mcp_kbUpper8.getGpio());
    processGpio(gpio, inputs, size);
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

void mcp_init(MCP23008 mcp) {
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

void pollsterInitUpper() {
    mcp_init(mcp_kbUpper8);
}

void pollsterInitLower() {
    mcp_init(mcp_kbLower8);
}

void pollsterInitPeriph() {
    mcp_init(mcp_periph1);
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