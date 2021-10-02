//
// Created by mjrsk on 10/2/2021.
//
#include "MCP23008.h"

MCP23008::MCP23008() {
    _address = 0x20;
    init();
}

MCP23008::MCP23008(uint8_t address) {
    _address = address;
    init();
}

void MCP23008::writeRegister(uint8_t reg, uint8_t data) const {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission(true);
}

uint8_t MCP23008::readRegister(uint8_t reg) const {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(true);
    uint8_t data = 0;
    data = readByte();

    return data;
}

uint8_t MCP23008::readByte() const {
    uint8_t one = 1;
    Wire.requestFrom(_address, one);
    uint8_t data = 0;
    while (Wire.available()) {
        data = Wire.read();
    }

    return data;
}

void MCP23008::init() const {
    uint8_t ioconWord = 0b00100000; // IO to byte mode
    uint8_t gppuWord =  0b11111111; // All pull up resistors to on

    Wire.begin();
    writeRegister(_iodir, 0xff);
    writeRegister(_ipol, 0xff); // set reverse input polarity
    writeRegister(_gpinten, 0xff);
    writeRegister(_iocon, ioconWord);
    writeRegister(_gppu, gppuWord);
}

uint8_t MCP23008::getAddress() const {
    return _address;
}

uint8_t MCP23008::getIodir() const {
    return _iodir;
}

uint8_t MCP23008::getIpol() const {
    return _ipol;
}

uint8_t MCP23008::getGpinten() const {
    return _gpinten;
}

uint8_t MCP23008::getDefval() const {
    return _defval;
}

uint8_t MCP23008::getIntcon() const {
    return _intcon;
}

uint8_t MCP23008::getIocon() const {
    return _iocon;
}

uint8_t MCP23008::getGppu() const {
    return _gppu;
}

uint8_t MCP23008::getIntf() const {
    return _intf;
}

uint8_t MCP23008::getIntcap() const {
    return _intcap;
}

uint8_t MCP23008::getGpio() const {
    return _gpio;
}

uint8_t MCP23008::getOlat() const {
    return _olat;
}
