//
// Created by Michael Skiles on 9/10/21.
//
#include <inttypes.h>
#include <cstddef>
#include "lcd16x2.h"

size_t lcd16x2::print(const char *buffer) const {
    return _writer.print(buffer);
}

size_t lcd16x2::writeByte(const uint8_t data) {
    return _writer.sendByte(data);
}

size_t lcd16x2::writeBytes(const uint8_t *buffer, size_t size) {
    return _writer.sendBytes(buffer, size);
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

}

void lcd16x2::blinkCursor() const {
    _writer.sendActionCommand(0x0d);
}