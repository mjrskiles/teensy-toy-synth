//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_CALLBACKS_H
#define SYNTH_CALLBACKS_H

#include "Controller.h"
#include <HardwareSerial.h>
#include "MCP23008.h"
#include "buffers.h"
#include "io/InputSnapshot.h"
#include "VirtualInput.h"

MCP23008 mcp_periph1 = MCP23008(0x20);
MCP23008 mcp_kbUpper8 = MCP23008(0x21);
MCP23008 mcp_kbLower8 = MCP23008(0x22);

/*
 * Callback for the listener to use
 */
void noteButtonListenerCallback(InputSnapshot &snapshot) {
    Serial.printf("Calling back from button %s", snapshot.name());
}

/*
 * Lower 8 Pollster cb
 */
void lower8PollsterCallback(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_kbLower8.readRegister(mcp_kbLower8.getGpio());
    Serial.println("-Lower 8 Pollster-");
    Serial.printf("gpio: %x\n", gpio);

    //put the data in the buffer
//    for(int i = 0; i < size; i++) {
////        bool isOn = (1 << i) & gpio;
//        bool isOn = true;
//        Serial.printf("In%n : %s\n", i, isOn ? "true" : "false");
//        if (isOn) {
//            Serial.printf("read button on at: %n", i);
//        }
//        VirtualInput input = inputs[i];
//        String nameTest = String("in") +i;
//        InputSnapshotBool snapshot = InputSnapshotBool("nameTest", isOn);
//        INPUT_BUFFER_BOOL[input.getIndex()] = snapshot;
//    }
    Serial.println("Lower pollster end");
}

void upper8PollsterCallback(VirtualInput *inputs, uint8_t size) {
    uint8_t gpio = mcp_kbUpper8.readRegister(mcp_kbUpper8.getGpio());
    Serial.println("-Upper 8 Pollster-");
    Serial.printf("gpio: %x\n", gpio);

    //put the data in the buffer

    Serial.println("upper pollster end");
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