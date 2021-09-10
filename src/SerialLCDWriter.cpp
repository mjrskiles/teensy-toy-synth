//
// Created by Michael Skiles on 9/10/21.
//

#include "SerialLCDWriter.h"
#define LCD_SERIAL Serial7

#include <Wire.h>
#include <inttypes.h>
#include <stddef.h>

void SerialLCDWriter::sendActionCommand(uint8_t command) const {
    LCD_SERIAL.write(0xfe);
    LCD_SERIAL.write(command);
}

void SerialLCDWriter::sendConfigCommand(uint8_t command) const {
    LCD_SERIAL.write(0x7c);
    LCD_SERIAL.write(command);
}

size_t SerialLCDWriter::sendByte(uint8_t data) const {
    return LCD_SERIAL.write(data);
}

size_t SerialLCDWriter::sendBytes(const uint8_t *buffer, size_t size) const {
    return 0;
}

uint8_t SerialLCDWriter::sendCommand(uint8_t commandChar, uint8_t command) const {
    LCD_SERIAL.write(commandChar);
    LCD_SERIAL.write(command);
    return 2;
}

size_t SerialLCDWriter::print(const char *buffer) const {
    return LCD_SERIAL.print(buffer);
}
