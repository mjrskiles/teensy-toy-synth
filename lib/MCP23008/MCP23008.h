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
    explicit MCP23008(uint8_t address);
    void writeRegister(uint8_t reg, uint8_t data) const;
    uint8_t readRegister(uint8_t reg) const;
    uint8_t readByte() const;
    void init() const;

    uint8_t getAddress() const;

    uint8_t getIodir() const;

    uint8_t getIpol() const;

    uint8_t getGpinten() const;

    uint8_t getDefval() const;

    uint8_t getIntcon() const;

    uint8_t getIocon() const;

    uint8_t getGppu() const;

    uint8_t getIntf() const;

    uint8_t getIntcap() const;

    uint8_t getGpio() const;

    uint8_t getOlat() const;

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

#endif //SYNTH_MCP23008_H
