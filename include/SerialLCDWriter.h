//
// Created by Michael Skiles on 9/10/21.
//

#ifndef SYNTH_SERIALLCDWRITER_H
#define SYNTH_SERIALLCDWRITER_H

#include <inttypes.h>
#include <stddef.h>

class SerialLCDWriter {
public:
    void sendActionCommand(uint8_t command) const;
    void sendConfigCommand(uint8_t command) const;
    size_t sendByte(uint8_t data) const;
    size_t sendBytes(const uint8_t *buffer, size_t size) const;
    size_t print(const char *buffer) const;
private:
    uint8_t _address;
    uint8_t sendCommand(uint8_t commandChar, uint8_t command) const;
};

#endif //SYNTH_SERIALLCDWRITER_H
