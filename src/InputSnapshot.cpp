//
// Created by Michael Skiles on 9/21/21.
//

#include "io/InputSnapshot.h"

// BASE
const char *InputSnapshot::name() {
    return _name;
}

pgmtime_t InputSnapshot::time() const{
    return _time;
}

InputDataType InputSnapshot::type() const {
    return _dataType;
}

InputSnapshot::InputSnapshot() {
    _name = "InputSnapshot base class default";
    _time = millis();
    _dataType = BOOL;
}

void InputSnapshot::setName(const char *newName) {
    _name = newName;
}

void InputSnapshot::setTime(pgmtime_t newTime) {
    _time = newTime;
}

// BOOL
String InputSnapshotBool::toString() {
    return _state ? "true" : "false";
}

bool InputSnapshotBool::asBool() {
    return _state;
}

float InputSnapshotBool::asFloat() {
    return _state ? 1.0f : 0.0f;
}

uint8_t InputSnapshotBool::asUint8() {
    return _state ? 1 : 0;
}

int16_t InputSnapshotBool::asInt16() {
    return _state ? 1 : 0;
}

InputSnapshotBool::InputSnapshotBool() {
    _name = "Bool Not set";
    _time = millis();
    _dataType = BOOL;
    _state = false;
}

// FLOAT
String InputSnapshotFloat::toString() {
    String value = String(_state);
    return value;
}

bool InputSnapshotFloat::asBool() {
    return _state != 0.0f;
}

float InputSnapshotFloat::asFloat() {
    return _state;
}

uint8_t InputSnapshotFloat::asUint8() {
    return static_cast<uint8_t>(_state);
}

int16_t InputSnapshotFloat::asInt16() {
    return static_cast<int16_t>(_state);
}

InputSnapshotFloat::InputSnapshotFloat() {
    _name = "Input snapshot float default";
    _time = millis();
    _dataType = FLOAT;
    _state = 0.0f;
}

// UINT8
String InputSnapshotUint8::toString() {
    return String(_state);
}

bool InputSnapshotUint8::asBool() {
    return _state != 0;
}

float InputSnapshotUint8::asFloat() {
    return static_cast<float>(_state);
}

uint8_t InputSnapshotUint8::asUint8() {
    return _state;
}

int16_t InputSnapshotUint8::asInt16() {
    return static_cast<int16_t>(_state);
}

InputSnapshotUint8::InputSnapshotUint8() {
    _name = "InputSnapshotUint8 default";
    _time = millis();
    _dataType = UINT8;
    _state = 0;
}

//INT16
String InputSnapshotInt16::toString() {
    return String(_state);
}

bool InputSnapshotInt16::asBool() {
    return _state != 0;
}

float InputSnapshotInt16::asFloat() {
    return static_cast<float>(_state);
}

uint8_t InputSnapshotInt16::asUint8() {
    return _state > 255 ? 255 : _state;
}

int16_t InputSnapshotInt16::asInt16() {
    return _state;
}

InputSnapshotInt16::InputSnapshotInt16() {
    _name = "InputSnapshotInt16 default";
    _time = millis();
    _dataType = UINT8;
    _state = 0;
}
