//
// Created by Michael Skiles on 9/30/21.
//

#include "io/display/Layout.h"

// Update each layout item and assemble them into the topBuffer
void Layout::updateGroup() {
    for (int i = 0; i < size; i++) {
        layoutItems[i].update_cb(layoutItems[i].buffer);
        // put the bytes into the group's topBuffer
        for (int j = 0; j < layoutItems[i].size; j++) {
            topBuffer[layoutItems[i].screenPosition + j] = layoutItems[i].buffer[j];
        }
    }

}

Layout::Layout(LayoutItem *layoutItems, size_t size, lcd_char *buffer, lcd_char *buffer2) : layoutItems(layoutItems), size(size),
                                                                         topBuffer(buffer), botBuffer(buffer2) {}

LayoutItem::LayoutItem(uint8_t screenPosition, lcd_char *buffer, size_t size, void (*updateCb)(lcd_char *))
        : screenPosition(screenPosition), buffer(buffer), size(size), update_cb(updateCb) {}
