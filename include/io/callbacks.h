//
// Created by Michael Skiles on 9/11/21.
//

#ifndef SYNTH_CALLBACKS_H
#define SYNTH_CALLBACKS_H

#include "Controller.h"
#include <HardwareSerial.h>
#include "../../lib/MCP23008/MCP23008.h"
#include "buffers/buffers.h"
#include "io/InputSnapshot.h"
#include "VirtualInput.h"
#include "tables/luts.h"
#include "synthesizer/synthesizer.h"
#include "buffers/buf_utils.h"

extern MCP23008 mcp_periph1;
extern MCP23008 mcp_kbUpper8;
extern MCP23008 mcp_kbLower8;

/*
 * Callback for the listener to use
 */
extern void cb_noteButtonListener(InputSnapshot &snapshot);
extern void cb_periphLogListener(InputSnapshot &snapshot);
extern void cb_processGpio(uint8_t gpioWord, VirtualInput *inputs, uint8_t size);

/*
 * Lower 8 Pollster cb
 */
extern void cb_lower8Pollster(VirtualInput *inputs, uint8_t size);
extern void cb_upper8Pollster(VirtualInput *inputs, uint8_t size);
extern void cb_peripheralPollster(VirtualInput *inputs, uint8_t size);

/*
 * Callback for the pollster, uses the MCP23008 to get the button state
 */
extern void note0PollsterCallback();
extern void cb_mcpInit(MCP23008 mcp);
extern void cb_pollsterInitUpper();
extern void cb_pollsterInitLower();
extern void cb_pollsterInitPeriph();

/*
 *  Display Layouts
 */
extern void cb_LayoutMcpLower(lcd_char *buffer);
extern void cb_LayoutMcpUpper(lcd_char *buffer);
extern void cb_LayoutCurrentNoteName(lcd_char *buffer);

#endif //SYNTH_CALLBACKS_H
