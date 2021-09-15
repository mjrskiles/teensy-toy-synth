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
extern void noteButtonListenerCallback(InputSnapshot<VirtualButtonState> snapshot) {
    Serial.printf("Calling back from button %s", snapshot.name);
}

/*
 * Callback for the pollster, uses the MCP23008 to get the button state
 */
extern VirtualButtonState note0PollsterCallback() {
    uint8_t gpio = ~(kbUpper8.readRegister(0x09)); // check the io register
    // check  if note 0 is active
    VirtualButtonState state = VirtualButtonState((gpio & 1));
    return state;
}

extern void pollsterInit() {
    kbUpper8.init();
    delay(100);
}



class InputTester {
public:
    InputTester(const char *nametest, const VirtualInput<VirtualButtonState> &note0,
                const InputListener<VirtualButtonState> &noteButtonListener,
                const InputPollster<VirtualButtonState> &pollsterUpper8);

    void init();



private:
    const char* nametest;
    VirtualInput<VirtualButtonState> _note0;
    InputListener<VirtualButtonState> _noteButtonListener;
    InputPollster<VirtualButtonState> _pollsterUpper8;
};

InputTester::InputTester(const char *nametest, const VirtualInput<VirtualButtonState> &note0,
                         const InputListener<VirtualButtonState> &noteButtonListener,
                         const InputPollster<VirtualButtonState> &pollsterUpper8) : nametest(nametest), _note0(note0),
                                                                                    _noteButtonListener(
                                                                                            noteButtonListener),
                                                                                    _pollsterUpper8(pollsterUpper8) {}

void InputTester::init() {
    _note0.addListener(_noteButtonListener);
    _pollsterUpper8.addInput(_note0);

}

#endif //SYNTH_INPUTCONTROLLERS_H
