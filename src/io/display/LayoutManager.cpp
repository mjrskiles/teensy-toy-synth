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
            Serial.println("Updating layout manager...");
            _currentLayout.updateGroup();
            Serial.println("Done updating group");
            _lcd.clearDisplay();
            _lcd.setCursorPosition(LCD_LINE_1_START_POS); // TODO get the real cursor pos out of a lookup table
            _lcd.writeBytes((uint8_t*) _currentLayout.topBuffer, 16);
            Serial.println("Done line1");
            _lcd.setCursorPosition(LCD_LINE_2_START_POS);
            _lcd.writeBytes(reinterpret_cast<const uint8_t *>(_currentLayout.botBuffer), 16); // write the 16 bytes of the 2nd line
            Serial.println("Done line2");
        }
        _updateTicker = 0;
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

LayoutManager::LayoutManager(lcd16x2 &lcd, const Layout &currentLayout) : _lcd(lcd), _currentLayout(currentLayout) {}
