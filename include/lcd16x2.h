//
// Created by Michael Skiles on 9/10/21.
//

#ifndef SYNTH_LCD16X2_H
#define SYNTH_LCD16X2_H
#include "SerialLCDWriter.h"
#include "synth_defines.h"

const uint8_t DISPLAY_COMMAND_CHAR = 0xFE;
const uint8_t DISPLAY_CONFIG_CHAR = 0x7C;
const uint8_t FE_CLEAR_DISPLAY = 0x01;
const uint8_t FE_CURSOR_RIGHT = 0x14;
const uint8_t FE_CURSOR_LEFT = 0x10;
const uint8_t FE_SCROLL_RIGHT = 0x1C;
const uint8_t FE_SCROLL_LEFT = 0x18;
const uint8_t FE_DISPLAY_ON_HIDE_CURSOR = 0x0C;
const uint8_t FE_DISPLAY_OFF = 0x08;
const uint8_t FE_SET_CURSOR_POS = 0x80;

//TODO fix the method for sending multiple bytes
class lcd16x2 {
public:
    lcd16x2(SerialLCDWriter writer) : _writer(writer) {}
    size_t print(const char *buffer) const;
    size_t writeByte(const uint8_t data);
    size_t writeBytes(const uint8_t *buffer, size_t size);
    size_t writeBuffer(const uint8_t buffer[LCD_ROWS * LCD_COLS]);
    void clearDisplay() const;
    void cursorRight() const;
    void cursorLeft() const;
    void scrollRight() const;
    void scrollLeft() const;
    void displayOn() const;
    void hideCursor() const;
    void blinkCursor() const;
    void displayOff() const;
    void setCursorPosition(uint8_t pos) const;
private:
    uint8_t _row;
    uint8_t _col;
    uint8_t _bufferA[32];
    uint8_t _bufferB[32];
    SerialLCDWriter _writer;
};

#endif //SYNTH_LCD16X2_H
