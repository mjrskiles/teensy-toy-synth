//
// Created by Michael Skiles on 9/10/21.
//
#include <inttypes.h>
#include <cstddef>
#include "io/display/lcd16x2.h"
#include "io/display/SerialLCDWriter.h"

size_t lcd16x2::print(const char *buffer) const {
    return _writer.print(buffer);
}

size_t lcd16x2::writeByte(const uint8_t data) {
    return _writer.sendByte(data);
}

size_t lcd16x2::writeBytes(const uint8_t *buffer, size_t size) {
    return _writer.sendBytes(buffer, size);
}

size_t lcd16x2::writeBuffer(const uint8_t buffer[LCD_ROWS * LCD_COLS]) {
    for (int i = 0; i < LCD_COLS; i++) {
        _writer.sendByte(buffer[i]);
    }
    setCursorPosition(LCD_LINE_2_START_POS);
    for (int i = 0; i < LCD_COLS; i++) {
        _writer.sendByte(buffer[i + LCD_COLS]);
    }
}

void lcd16x2::clearDisplay() const {
    _writer.sendActionCommand(FE_CLEAR_DISPLAY);
}

void lcd16x2::cursorRight() const {
    _writer.sendActionCommand(FE_CURSOR_RIGHT);
}

void lcd16x2::cursorLeft() const {
    _writer.sendActionCommand(FE_CURSOR_LEFT);
}

void lcd16x2::scrollRight() const {
    _writer.sendActionCommand(FE_SCROLL_RIGHT);
}

void lcd16x2::scrollLeft() const {
    _writer.sendActionCommand(FE_SCROLL_LEFT);
}

void lcd16x2::displayOn() const {
    _writer.sendActionCommand(FE_DISPLAY_ON_HIDE_CURSOR);
}

void lcd16x2::hideCursor() const {
    _writer.sendActionCommand(FE_DISPLAY_ON_HIDE_CURSOR);
}

void lcd16x2::displayOff() const {
    _writer.sendActionCommand(FE_DISPLAY_OFF);
}

void lcd16x2::setCursorPosition(uint8_t pos) const {
    _writer.sendByte(0xfe);
    _writer.sendByte(pos + 128);
}

void lcd16x2::blinkCursor() const {
    _writer.sendActionCommand(0x0d);
}

void lcd16x2::userSplash() {
    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');

    writeByte((uint8_t)' ');
    writeByte((uint8_t)'t');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)'o');

    writeByte((uint8_t)' ');
    writeByte((uint8_t)'y');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');

    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');

    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)'s');

    writeByte((uint8_t)' ');
    writeByte((uint8_t)'y');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)'n');

    writeByte((uint8_t)' ');
    writeByte((uint8_t)'t');
    writeByte((uint8_t)' ');
    writeByte((uint8_t)'h');
}
