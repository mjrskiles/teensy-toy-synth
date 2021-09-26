//
// Created by mjrsk on 9/20/2021.
//

#ifndef SYNTH_COMPONENTS_H
#define SYNTH_COMPONENTS_H
#include "io/InputSnapshot.h"
#include "io/InputPollster.h"
#include "io/Callbacks.h"

// the callbacks are defined in inputcontrollers.h
void (*listener_callback)(InputSnapshot&) = &noteButtonListenerCallback;
void (*pollCallback)(VirtualInput *inputs, uint8_t size) = &lower8PollsterCallback;
void (*upperPollCallback)(VirtualInput *inputs, uint8_t size) = &upper8PollsterCallback;
void (*initCallback)() = &pollsterInit;

InputListener note0Listeners[] = {
        InputListener(listener_callback,"note0"),
        };
InputListener note1Listeners[] = {
        InputListener(listener_callback,"note1"),
        };
InputListener note2Listeners[] = {
        InputListener(listener_callback,"note2"),
        };
InputListener note3Listeners[] = {
        InputListener(listener_callback,"note3"),
        };
InputListener note4Listeners[] = {
        InputListener(listener_callback,"note4"),
        };
InputListener note5Listeners[] = {
        InputListener(listener_callback,"note5"),
        };
InputListener note6Listeners[] = {
        InputListener(listener_callback,"note6"),
        };
InputListener note7Listeners[] = {
        InputListener(listener_callback,"note7"),
        };
InputListener note8Listeners[] = {
        InputListener(listener_callback,"note8"),
        };
InputListener note9Listeners[] = {
        InputListener(listener_callback,"note9"),
        };
InputListener note10Listeners[] = {
        InputListener(listener_callback,"note10"),
        };
InputListener note11Listeners[] = {
        InputListener(listener_callback,"note11"),
        };
InputListener note12Listeners[] = {
        InputListener(listener_callback,"note12"),
        };
InputListener note13Listeners[] = {
        InputListener(listener_callback,"note13"),
        };
InputListener note14Listeners[] = {
        InputListener(listener_callback,"note14"),
        };
InputListener note15Listeners[] = {
        InputListener(listener_callback,"note15"),
        };

VirtualInput note0 = VirtualInput(note0Listeners, 1, 0, BOOL);
VirtualInput note1 = VirtualInput(note1Listeners, 1, 1 , BOOL);
VirtualInput note2 = VirtualInput(note2Listeners, 1, 2 , BOOL);
VirtualInput note3 = VirtualInput(note3Listeners, 1, 3 , BOOL);
VirtualInput note4 = VirtualInput(note4Listeners, 1, 4 , BOOL);
VirtualInput note5 = VirtualInput(note5Listeners, 1, 5 , BOOL);
VirtualInput note6 = VirtualInput(note6Listeners, 1, 6 , BOOL);
VirtualInput note7 = VirtualInput(note7Listeners, 1, 7 , BOOL);
VirtualInput note8 = VirtualInput(note8Listeners, 1, 8 , BOOL);
VirtualInput note9 = VirtualInput(note9Listeners, 1, 9 , BOOL);
VirtualInput note10 = VirtualInput(note10Listeners, 1, 10 , BOOL);
VirtualInput note11 = VirtualInput(note11Listeners, 1, 11 , BOOL);
VirtualInput note12 = VirtualInput(note12Listeners, 1, 12 , BOOL);
VirtualInput note13 = VirtualInput(note13Listeners, 1, 13 , BOOL);
VirtualInput note14 = VirtualInput(note14Listeners, 1, 14 , BOOL);
VirtualInput note15 = VirtualInput(note15Listeners, 1, 15 , BOOL);

VirtualInput mcpLower8VirtualInputs[] = {
        note0, note1, note2, note3,
        note4, note5, note6, note7
};
VirtualInput mcpUpper8VirtualInputs[] = {
        note8, note9, note10, note11,
        note12, note13, note14, note15
};

InputPollster pollsterLower8 = InputPollster(pollCallback,
                                             initCallback,
                                             mcpLower8VirtualInputs,
                                             (uint8_t)8);
InputPollster pollsterUpper8 = InputPollster(upperPollCallback,
                                             initCallback,
                                             mcpUpper8VirtualInputs,
                                             (uint8_t)8);

#endif //SYNTH_COMPONENTS_H
