//
// Created by Michael Skiles on 9/8/21.
//

#ifndef SYNTH_I2C1602_CPP_H
#define SYNTH_I2C1602_CPP_H

class I2C1602Writer {
public:
    explicit I2C1602Writer(uint8_t address);

    void sendActionCommand(uint8_t command) const;
    void sendConfigCommand(uint8_t command) const;
    size_t sendByte(uint8_t data) const;
    size_t sendBytes(const uint8_t *buffer, size_t size) const;
private:
    uint8_t _address;
    uint8_t sendCommand(uint8_t commandChar, uint8_t command) const;
};
#endif //SYNTH_I2C1602_CPP_H
