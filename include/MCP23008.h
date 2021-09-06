//
// Created by Michael Skiles on 9/2/21.
//

#ifndef SYNTH_MCP23008_H
#define SYNTH_MCP23008_H

#include <Wire.h>
#include <inttypes.h>

#define BUFFER_SIZE 32

class MCP23008 {
public:
    MCP23008();
    MCP23008(uint8_t address);
    void writeRegister(uint8_t reg, uint8_t data);
    uint8_t readRegister(uint8_t reg);
    uint8_t readByte();
    void init();

private:
    uint8_t _address;

    // MCP23008 register addresses
    uint8_t _iodir = 0x00;
    uint8_t _ipol = 0x01;
    uint8_t _gpinten = 0x02;
    uint8_t _defval = 0x03;
    uint8_t _intcon = 0x04;
    uint8_t _iocon = 0x05;
    uint8_t _gppu = 0x06;
    uint8_t _intf = 0x07;
    uint8_t _intcap = 0x08;
    uint8_t _gpio = 0x09;
    uint8_t _olat = 0x0A;
};

/*// Initialize class members*/
/*uint8_t MCP23008::_iodir = 0x00;*/
/*uint8_t MCP23008::_ipol = 0x01;*/
/*uint8_t MCP23008::_gpinten = 0x02*/;
/*uint8_t MCP23008::_defval = 0x03;*/
/*uint8_t MCP23008::_intcon = 0x04;*/
/*uint8_t MCP23008::_iocon = 0x05;*/
/*uint8_t MCP23008::_gppu = 0x06;*/
/*uint8_t MCP23008::_intf = 0x07;*/
/*uint8_t MCP23008::_intcap = 0x08;*/
/*uint8_t MCP23008::_gpio = 0x09;*/
/*uint8_t MCP23008::_olat = 0x0A;*/

MCP23008::MCP23008() {
    MCP23008(0x20); // Use default address from MCP23008 datasheet
}

MCP23008::MCP23008(uint8_t address) {
    _address = address;
    init();
}

void MCP23008::writeRegister(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission(true);
}

uint8_t MCP23008::readRegister(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(true);
    uint8_t one = 1;
    Wire.requestFrom(_address, one);

    uint8_t data = 0;
    while (Wire.available()) {
        data = Wire.read();
    }

    return data;
}

uint8_t MCP23008::readByte() {
    return 0;
}

void MCP23008::init() {
    uint8_t ioconWord = 1 << 4; // IO to byte mode
    uint8_t gppuWord = 0b11111111; // All pull up resistors to on

    Wire.begin();
    writeRegister(_iocon, ioconWord);
    writeRegister(_gppu, gppuWord);
}


#endif //SYNTH_MCP23008_H
