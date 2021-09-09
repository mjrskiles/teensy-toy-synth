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
    void sendByte(uint8_t data) const;
    void sendBytes(const uint8_t *buffer, size_t size) const;
private:
    uint8_t _address;
    uint8_t sendCommand(uint8_t commandChar, uint8_t command) const;
};

//TODO fix the method for sending multiple bytes
class lcd16x2 {
public:
    lcd16x2(I2C1602Writer writer) : _writer(writer) {}
    size_t writeByte(const uint8_t data);
    size_t writeBytes(const uint8_t *buffer, size_t size);
    void clearDisplay() const;
    void cursorRight() const;
    void cursorLeft() const;
    void scrollRight() const;
    void scrollLeft() const;
    void displayOn() const;
    void hideCursor() const;
    void displayOff() const;
    void setCursorPosition(uint8_t pos) const;
private:
    uint8_t _row;
    uint8_t _col;
    uint8_t _bufferA[32];
    uint8_t _bufferB[32];
    I2C1602Writer _writer;
};
#endif //SYNTH_I2C1602_CPP_H
