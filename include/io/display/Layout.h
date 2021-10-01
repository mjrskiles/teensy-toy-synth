//
// Created by Michael Skiles on 9/30/21.
//

#ifndef TEENSY_SYNTH_LAYOUT_H
#define TEENSY_SYNTH_LAYOUT_H

#include <toy_defines.h>
#include <inttypes.h>
#include <stddef.h>
#include <toy_types.h>

struct LayoutItem {
    uint8_t screenPosition; // line 1: 0-15, line 2: 16-31
    lcd_char *buffer;
    size_t size;
    /*
     * The callback should fetch its relevant data and update its own buffer;
     */
    void (*update_cb)();
};
struct Layout {
    LayoutItem *layoutItems;
    size_t size;
    void updateGroup();

    lcd_char buffer[LCD_ROWS * LCD_COLS];
};

#endif //TEENSY_SYNTH_LAYOUT_H
