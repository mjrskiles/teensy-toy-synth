//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_INPUTCONTROLLERS_H
#define SYNTH_INPUTCONTROLLERS_H

#include "Controller.h"
#include <HardwareSerial.h>
#include "MCP23008.h"


class VirtualButtonState {
public:
    VirtualButtonState(bool state) : _state(state) {}

    bool state() { return _state; }
private:
    bool _state;
};

MCP23008 kbUpper8 = MCP23008(0x21);

/*
 * Callback for the listener to use
 */
VirtualButtonState noteButtonListenerCallback(InputSnapshot<VirtualButtonState> snapshot) {
    Serial.printf("Calling back from button %s", snapshot.name);
    return snapshot.data;
}

/*
 * Callback for the pollster, uses the MCP23008 to get the button state
 */
VirtualButtonState note0PollsterCallback() {
    uint8_t gpio = ~(kbUpper8.readRegister(0x09)); // check the io register
    // check  if note 0 is active
    VirtualButtonState state = VirtualButtonState((gpio & 1));
    return state;
}

void pollsterInit() {
    kbUpper8.init();
    delay(100);
}

class InputTester {
public:
    void init() {
        note0.addListener(noteButtonListener);
        pollsterUpper8.addInput(note0);

    }



private:
    const char* nametest = "button0!";
    VirtualInput<VirtualButtonState> note0 = VirtualInput<VirtualButtonState>();
    InputListener<VirtualButtonState> noteButtonListener = InputListener<VirtualButtonState>(&noteButtonListenerCallback,
                                                                                             nametest);
    InputPollster<VirtualButtonState> pollsterUpper8 = InputPollster<VirtualButtonState>(&note0PollsterCallback,
                                                                                         &pollsterInit);
};

#endif //SYNTH_INPUTCONTROLLERS_H
