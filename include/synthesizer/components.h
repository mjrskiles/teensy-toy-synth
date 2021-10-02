//
// Created by mjrsk on 9/20/2021.
//

#ifndef SYNTH_COMPONENTS_H
#define SYNTH_COMPONENTS_H

#include <io/display/Layout.h>
#include <io/display/LayoutManager.h>
#include "io/InputSnapshot.h"
#include "io/InputPollster.h"
#include "io/callbacks.h"

// the callbacks are defined in callbacks.h
// Listeners
extern void (*listener_callback)(InputSnapshot&);
extern void (*periphLogCallback)(InputSnapshot&);

// Pollsters
//   polling
extern void (*pollCallback)(VirtualInput *inputs, uint8_t size);
extern void (*upperPollCallback)(VirtualInput *inputs, uint8_t size);
extern void (*periphPollCallback)(VirtualInput *inputs, uint8_t size);
//   init
extern void (*initCallbackUpper)();
extern void (*initCallbackLower)();
extern void (*initCallbackPeriph)();

extern InputListener note0Listeners[];
extern InputListener note1Listeners[];
extern InputListener note2Listeners[];
extern InputListener note3Listeners[];
extern InputListener note4Listeners[];
extern InputListener note5Listeners[];
extern InputListener note6Listeners[];
extern InputListener note7Listeners[];
extern InputListener note8Listeners[];
extern InputListener note9Listeners[];
extern InputListener note10Listeners[];
extern InputListener note11Listeners[];
extern InputListener note12Listeners[];
extern InputListener note13Listeners[];
extern InputListener note14Listeners[];
extern InputListener note15Listeners[];

extern InputListener selectorSwitch1Listeners[];
extern InputListener selectorSwitch2Listeners[];
extern InputListener selectorSwitch3Listeners[];
extern InputListener pb1Listeners[];
extern InputListener pb2Listeners[];

extern VirtualInput note0;
extern VirtualInput note1;
extern VirtualInput note2;
extern VirtualInput note3;
extern VirtualInput note4;
extern VirtualInput note5;
extern VirtualInput note6;
extern VirtualInput note7;
extern VirtualInput note8;
extern VirtualInput note9;
extern VirtualInput note10;
extern VirtualInput note11;
extern VirtualInput note12;
extern VirtualInput note13;
extern VirtualInput note14;
extern VirtualInput note15;

extern VirtualInput ss1;
extern VirtualInput ss2;
extern VirtualInput ss3;
extern VirtualInput pb1;
extern VirtualInput pb2;

extern VirtualInput mcpLower8VirtualInputs[];
extern VirtualInput mcpUpper8VirtualInputs[];

extern VirtualInput mcpPeripheralInputs[];

extern InputPollster pollsterLower8;
extern InputPollster pollsterUpper8;
extern InputPollster pollsterPeriph;

/*
 * DISPLAY LAYOUTS
 */
extern LayoutItem layoutItem_mcpLower;
extern LayoutItem layoutItem_mcpUpper;
extern LayoutItem layoutItem_noteName;
extern LayoutItem layoutItems[];
extern Layout layout_noteIO;

#endif //SYNTH_COMPONENTS_H
