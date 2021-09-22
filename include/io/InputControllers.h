//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_INPUTCONTROLLERS_H
#define SYNTH_INPUTCONTROLLERS_H

#include "Controller.h"
#include <HardwareSerial.h>
#include "MCP23008.h"
#include "synthesizer/synthesizer.h"
#include "Globals.h"
#include "io/InputSnapshot.h"

MCP23008 kbUpper8 = MCP23008(0x21);

/*
 * Callback for the listener to use
 */
void noteButtonListenerCallback(InputSnapshot &snapshot) {
    Serial.printf("Calling back from button %s", snapshot.name());
}

/*
 * Callback for the pollster, uses the MCP23008 to get the button state
 */
void* note0PollsterCallback() {
    uint8_t gpio = kbUpper8.readRegister(0x09); // check the io register
    // check  if note 0 is active
    Serial.println("pollster _callback:");
    Serial.printf(" value: %x\n", gpio);
}

void pollsterInit() {
    Serial.println("Begin mcp init block");
    Serial.println("constructor");
    kbUpper8.init();
    Serial.println("init");
    delay(100);
    uint8_t iocon = kbUpper8.readRegister(0x05); // check the iocon register
    Serial.println("iocon read");
    Serial.printf("MCP IOCON reg: %hhu\n", iocon);
    uint8_t gppu = kbUpper8.readRegister(0x06);
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

#endif //SYNTH_INPUTCONTROLLERS_H