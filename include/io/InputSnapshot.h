//
// Created by Michael Skiles on 9/21/21.
//

#ifndef SYNTH_INPUTSNAPSHOT_H
#define SYNTH_INPUTSNAPSHOT_H

#include <Arduino.h>
#include "toy_types.h"

enum InputDataType : uint8_t {
    BOOL,
    FLOAT,
    UINT8,
    INT16
};

/*
 * base class for input data
 *
 * can fetch its data as a string, bool, float, uint8 or int16, depending on
 * the underlying data
 */
class InputSnapshot {
public:
    InputSnapshot();

    const char* name();
    pgmtime_t time() const;
    InputDataType type() const;

    virtual String toString() = 0;
    virtual bool asBool()     = 0;
    virtual float asFloat()   = 0;
    virtual uint8_t asUint8() = 0;
    virtual int16_t asInt16() = 0;

    void setName(const char *newName);
    void setTime(pgmtime_t newTime);

    void setDataType(InputDataType dataType);

    void setFromIndex(int fromIndex);

    int getFromIndex() const;

protected:
    const char* _name;
    pgmtime_t _time;
    InputDataType _dataType;
    int _fromIndex;
};

class InputSnapshotBool : public InputSnapshot {
public:
    InputSnapshotBool();

    InputSnapshotBool(const char *name, bool state) {
        _name = name;
        _time = millis();
        _dataType = BOOL;
        _state = state;
    }

    String toString()  override;
    bool asBool()     override;
    float asFloat()   override;
    uint8_t asUint8() override;
    int16_t asInt16() override;

    void setState(boolean state);
protected:
    bool _state;
};

class InputSnapshotFloat : public InputSnapshot {
public:
    InputSnapshotFloat();

    InputSnapshotFloat(const char *name, float state) {
        _name = name;
        _time = millis();
        _dataType = FLOAT;
        _state = state;
    }

    String toString()  override;
    bool asBool()     override;
    float asFloat()   override;
    uint8_t asUint8() override;
    int16_t asInt16() override;

protected:
    float _state;
};

class InputSnapshotUint8 : public InputSnapshot {
public:
    InputSnapshotUint8();

    InputSnapshotUint8(const char *name, uint8_t state) {
        _name = name;
        _time = millis();
        _dataType = UINT8;
        _state = state;
    }

    String toString()  override;
    bool asBool()     override;
    float asFloat()   override;
    uint8_t asUint8() override;
    int16_t asInt16() override;

protected:
    uint8_t _state;
};

class InputSnapshotInt16 : public InputSnapshot {
public:
    InputSnapshotInt16();

    InputSnapshotInt16(const char *name, int16_t state) {
        _name = name;
        _time = millis();
        _dataType = UINT8;
        _state = state;
    }

    String toString()  override;
    bool asBool()     override;
    float asFloat()   override;
    uint8_t asUint8() override;
    int16_t asInt16() override;

protected:
    int16_t _state;
};

#endif //SYNTH_INPUTSNAPSHOT_H
