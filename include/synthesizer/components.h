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

LayoutItem li_Test1 = LayoutItem(0, LCD_LAYOUT_TEST1, 16, cb_LayoutTest1);
LayoutItem li_Test2 = LayoutItem(0, LCD_LAYOUT_TEST1, 16, cb_LayoutTest2);
LayoutItem layoutItemsP2[]{li_Test1};
LayoutItem layoutItemsP3[]{li_Test2};
Layout layout_P2 = Layout(layoutItemsP2, 1, LCD_DISP_BACK_BUFFER);
Layout layout_P3 = Layout(layoutItemsP3, 1, LCD_DISP_BACK_BUFFER);

Layout layouts[NUM_LAYOUTS] {layout_noteIO, layout_P2, layout_P3};
#endif //SYNTH_COMPONENTS_H
