//
// Created by Michael Skiles on 9/30/21.
//

#include "io/display/Layout.h"

// Update each layout item and assemble them into the buffer
void Layout::updateGroup() {
    for (int i = 0; i < size; i++) {
        layoutItems[i].update_cb(layoutItems[i].buffer);
        // put the bytes into the group's buffer
        for (int j = 0; i < layoutItems[i].size; j++) {
            buffer[layoutItems[i].screenPosition + j] = layoutItems[i].buffer[j];
        }
    }

}

Layout::Layout(LayoutItem *layoutItems, size_t size, lcd_char *buffer) : layoutItems(layoutItems), size(size),
                                                                         buffer(buffer) {}

LayoutItem::LayoutItem(uint8_t screenPosition, lcd_char *buffer, size_t size, void (*updateCb)(lcd_char *))
        : screenPosition(screenPosition), buffer(buffer), size(size), update_cb(updateCb) {}
