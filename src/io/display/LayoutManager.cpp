//
// Created by Michael Skiles on 9/30/21.
//

#include "io/display/LayoutManager.h"

void LayoutManager::startCyclicUpdate() {
    _runLayoutFlag = true;
}

void LayoutManager::update() {
    if (_updateTicker >= 1000 / LCD_UPDATE_HZ) {
        if (_runLayoutFlag) {
            _currentLayout.updateGroup();
            _lcd.setCursorPosition(LCD_LINE_1_START_POS);
            _lcd.writeBytes(_currentLayout.buffer, 16);
            _lcd.setCursorPosition(LCD_LINE_2_START_POS);
            _lcd.writeBytes((_currentLayout.buffer + 16), 16); // write the 16 bytes of the 2nd line
        }
    }
}

void LayoutManager::setLayout(Layout &layout) {
    _currentLayout = layout;
}

void LayoutManager::runLayout() {
    _runLayoutFlag = true;
}

void LayoutManager::stopLayout() {
    _runLayoutFlag = false;
}
