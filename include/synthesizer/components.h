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

// Pollsters
//   polling
void (*pollCallback)() = &cb_lower8Pollster;
void (*upperPollCallback)() = &cb_upper8Pollster;
void (*periphPollCallback)() = &cb_peripheralPollster;
//   init
void (*initCallbackUpper)() = &cb_pollsterInitUpper;
void (*initCallbackLower)() = &cb_pollsterInitLower;
void (*initCallbackPeriph)() = &cb_pollsterInitPeriph;


InputPollster pollsterLower8 = InputPollster(pollCallback,
                                             initCallbackLower,
                                             (uint8_t)8);
InputPollster pollsterUpper8 = InputPollster(upperPollCallback,
                                             initCallbackUpper,
                                             (uint8_t)8);
InputPollster pollsterPeriph = InputPollster(periphPollCallback,
                                             initCallbackPeriph,
                                             (uint8_t)5);

/*
 * DISPLAY LAYOUTS
 */
LayoutItem layoutItem_mcpLower = LayoutItem(16, LCD_LAYOUT_BUFFER_MCP_LOWER, 8, cb_LayoutMcpLower);
LayoutItem layoutItem_mcpUpper = LayoutItem(0, LCD_LAYOUT_BUFFER_MCP_UPPER, 8, cb_LayoutMcpUpper);
LayoutItem layoutItem_noteName = LayoutItem(12, LCD_LAYOUT_BUFFER_NOTE_NAME, LCD_NOTE_NAME_CHAR_WIDTH,
                                            cb_LayoutCurrentNoteName);
LayoutItem layoutItems[] {layoutItem_mcpUpper, layoutItem_mcpLower, layoutItem_noteName};
Layout layout_noteIO = Layout(layoutItems, 3, LCD_DISP_BACK_BUFFER);

#endif //SYNTH_COMPONENTS_H
