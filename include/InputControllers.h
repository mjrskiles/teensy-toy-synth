//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_INPUTCONTROLLERS_H
#define SYNTH_INPUTCONTROLLERS_H

#include "Controller.h"
#include <HardwareSerial.h>
#include "MCP23008.h"
#include "synthesizer/synthesizer.h"

MCP23008 kbUpper8 = MCP23008(0x21);

/*
 * Callback for the listener to use
 */
extern void noteButtonListenerCallback(InputSnapshot snapshot) {
    Serial.printf("Calling back from button %s", snapshot.name);
}

/*
 * Callback for the pollster, uses the MCP23008 to get the button state
 */
extern void* note0PollsterCallback() {
    uint8_t gpio = kbUpper8.readRegister(0x09); // check the io register
    // check  if note 0 is active
    VirtualButtonState state = VirtualButtonState((gpio & 1));
    Serial.println("pollster callback:");
    Serial.printf(" value: %x\n", gpio);
    return (void*)&state;
}

extern void pollsterInit() {
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



class InputTester {
public:
    InputTester(const char *nametest, const VirtualInput &note0,
                const InputListener &noteButtonListener,
                const InputPollster &pollsterUpper8);

    void init();



private:
    const char* nametest;
    VirtualInput _note0;
    InputListener _noteButtonListener;
    InputPollster _pollsterUpper8;
};

InputTester::InputTester(const char *nametest, const VirtualInput &note0,
                         const InputListener &noteButtonListener,
                         const InputPollster &pollsterUpper8) : nametest(nametest), _note0(note0),
                                                                                    _noteButtonListener(
                                                                                            noteButtonListener),
                                                                                    _pollsterUpper8(pollsterUpper8) {}

void InputTester::init() {
    _note0.addListener(_noteButtonListener);
    _pollsterUpper8.addInput(_note0);

}

/***************************
 * Note button listeners
 */
void logCallback(InputSnapshot snapshot) {
    Serial.printf("Logback from %s\n", snapshot.name);
    Serial.printf("Payload: ");
    switch (snapshot.dataType) {
        case BOOL:
            Serial.printf("%s", (bool) (snapshot.data) ? "true" : "false");
        case CONTINUOUS_INTEGER:
            Serial.printf("%d", (int)snapshot.data);
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
