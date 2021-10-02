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
    LayoutItem(uint8_t screenPosition, lcd_char *buffer, size_t size, void (*updateCb)(lcd_char *));

    uint8_t screenPosition; // line 1: 0-15, line 2: 16-31
    lcd_char *buffer;
    size_t size;
    /*
     * The callback should fetch its relevant data and update its own topBuffer;
     */
    void (*update_cb)(lcd_char *buffer);
};
struct Layout {
    Layout(LayoutItem *layoutItems, size_t size, lcd_char *bufTop, lcd_char *bufBot);

    LayoutItem *layoutItems;
    size_t size;
    void updateGroup();

    lcd_char *topBuffer;
    lcd_char *botBuffer;
    size_t bufSize = LCD_ROWS * LCD_COLS;
};

#endif //TEENSY_SYNTH_LAYOUT_H
