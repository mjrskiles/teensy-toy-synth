//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_INPUTCONTROLLERS_H
#define SYNTH_INPUTCONTROLLERS_H

#include "Controller.h"
#include <HardwareSerial.h>
#include "../include/MCP23008.h"

MCP23008 kbUpper8 = MCP23008(0x21);

/*
 * Callback for the listener to use
 */
extern void noteButtonListenerCallback(InputSnapshot snapshot) {
    Serial.printf("Calling back from button %s", snapshot._name);
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

#endif //SYNTH_INPUTCONTROLLERS_H
