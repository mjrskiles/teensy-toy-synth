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
    uint8_t writeRegister(uint8_t reg, uint8_t data);
    uint8_t readRegister(uint8_t reg);
    uint8_t readByte();
    void init();

private:
    uint8_t _address;

    // MCP23008 register addresses
    uint8_t _iodir;
    uint8_t _ipol;
    uint8_t _gpinten;
    uint8_t _defval;
    uint8_t _intcon;
    uint8_t _iocon;
    uint8_t _gppu;
    uint8_t _intf;
    uint8_t _intcap;
    uint8_t _gpio;
    uint8_t _olat;
};

MCP23008::MCP23008() {
    MCP23008::MCP23008(0x20); // Use default address from MCP23008 datasheet
}

MCP23008::MCP23008(uint8_t address) {
    _address = address;
    init();
}

uint8_t MCP23008::writeRegister(uint8_t reg, uint8_t data) {
    return 0;
}

uint8_t MCP23008::readRegister(uint8_t reg) {
    return 0;
}

uint8_t MCP23008::readByte() {
    return 0;
}

void MCP23008::init() {
    Wire.begin();

}


#endif //SYNTH_MCP23008_H
