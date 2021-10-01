//
// Created by Michael Skiles on 9/30/21.
//

#include "io/display/Layout.h"

// Update each layout item and assemble them into the buffer
void Layout::updateGroup() {
    for (int i = 0; i < size; i++) {
        layoutItems[i].update_cb();
        // put the bytes into the group's buffer
        for (int j = 0; i < layoutItems[i].size; j++) {
            buffer[layoutItems[i].screenPosition + j] = layoutItems[i].buffer[j];
        }
    }

}
