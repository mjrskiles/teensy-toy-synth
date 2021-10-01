//
// Created by Michael Skiles on 9/5/21.
//

#include <Wire.h>
#include <inttypes.h>
#include "io/display/I2C1602.h"
#include "io/display/lcd16x2.h"


/*
 *
ctrl   | cmd     | description
char   |         |
-0xFE-- 0x01      Clear Display
        0x14      Move Cursor Right 1 Space
        0x10      Move Cursor Left 1 Space
        0x1C      Scroll Right 1 Space
        0x18      Scroll Left 1 Space
        0x0C      Turn Display On / Hide Cursor
        0x08      Turn Display Off
        0x0E      Underline Cursor On
        0x0D      Blinking Cursor On
        0x80 + n  Set Cursor Position
-0x7C-- 0x03      20 Characters Wide
        0x04      16 Characters Wide
        0x05      4 Lines
        0x06      2 Lines
        0x0A      Set Splash Screen
        0x0B      Set Baud Rate to 2400
        0x0C      Set Baud Rate to 4800
        0x0D      Set Baud Rate to 9600
        0x0E      Set Baud Rate to 14400
        0x0F      Set Baud Rate to 19200
        0x10      Set Baud Rate to 38400
        0x80      Backlight Off*
        0x9D      Backlight Fully On**/

#define DISPLAY_I2C Wire



// Parent class to implement the HD44780 commands and other useful helpers
class lcd1602Writer {
public:
    void sendActionCommand(uint8_t command) const {

    }

    void sendConfigCommand(uint8_t command) const {

    }

    void sendBytes(const char *buffer, size_t size) const {

    }
};


I2C1602Writer::I2C1602Writer(uint8_t address) {
    _address = address;
    DISPLAY_I2C.begin();
}

void I2C1602Writer::sendActionCommand(uint8_t command) const {
    sendCommand(DISPLAY_COMMAND_CHAR, command);
}
void I2C1602Writer::sendConfigCommand(uint8_t command) const {
    sendCommand(DISPLAY_CONFIG_CHAR, command);
}

size_t I2C1602Writer::sendByte(uint8_t data) const {
    DISPLAY_I2C.beginTransmission(_address);
    size_t amountWritten = DISPLAY_I2C.write(data);
    DISPLAY_I2C.endTransmission();
//    Serial.printf("I2CWriter::sendByte wrote %n bytes!\n", amountWritten);
    return amountWritten;
}

size_t I2C1602Writer::sendBytes(const uint8_t *buffer, size_t size) const {
    DISPLAY_I2C.beginTransmission(_address);
    // send bytes one by one
    size_t amountWritten = 0;
    for (size_t i = 0; i < size; i++) {
        uint8_t byte = buffer[i];
        amountWritten += DISPLAY_I2C.write(byte);
    }
    DISPLAY_I2C.endTransmission();
//    Serial.printf("I2CWriter::sendBytes wrote %n bytes!\n", amountWritten);
    return amountWritten;
}
uint8_t I2C1602Writer::sendCommand(uint8_t commandChar, uint8_t command) const {
    size_t amountWritten = 0;
    DISPLAY_I2C.beginTransmission(_address);
    amountWritten += DISPLAY_I2C.write(commandChar);
    amountWritten += DISPLAY_I2C.write(command);
    DISPLAY_I2C.endTransmission();
//    Serial.printf("I2CWriter::sendCommand wrote %n bytes!\n", amountWritten);
    return 0; // TODO never update this to do anything
}























