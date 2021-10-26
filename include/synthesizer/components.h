//
// Created by mjrsk on 9/20/2021.
//

#ifndef SYNTH_COMPONENTS_H
#define SYNTH_COMPONENTS_H

#include <io/display/Layout.h>
#include <io/display/LayoutManager.h>
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

LayoutItem li_attack = LayoutItem(0, LCD_LAYOUT_ATTACK, 7, cb_LayoutAttack);
LayoutItem li_decay = LayoutItem(8, LCD_LAYOUT_DECAY, 7, cb_LayoutDecay);
LayoutItem li_sustain = LayoutItem(16, LCD_LAYOUT_SUSTAIN, 7, cb_LayoutSustain);
LayoutItem li_release = LayoutItem(24, LCD_LAYOUT_RELEASE, 7, cb_LayoutRelease);
LayoutItem li_Test2 = LayoutItem(0, LCD_LAYOUT_TEST2, 13, cb_LayoutTest2);
LayoutItem layoutItemsP2[]{li_attack, li_decay, li_sustain, li_release};
LayoutItem layoutItemsP3[]{li_Test2};
Layout layout_P2 = Layout(layoutItemsP2, 4, LCD_DISP_FRONT_BUFFER);
Layout layout_P3 = Layout(layoutItemsP3, 1, LCD_DISP_FRONT_BUFFER);

Layout layouts[NUM_LAYOUTS] {layout_noteIO, layout_P2, layout_P3};
#endif //SYNTH_COMPONENTS_H
