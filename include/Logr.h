//
// Created by mjrsk on 9/24/2021.
//

#ifndef TEENSY_SYNTH_LOGR_H
#define TEENSY_SYNTH_LOGR_H

#include <Arduino.h>

#define LOG Serial
#define LOG_INFO Serial
#define LOG_DEBUG Serial
#define LOG_ERROR Serial

class Logr {
public:
    void line(const char * line);
    void info(const char * line);
    void debug(const char * line);
    void error(const char * line);
};

#endif //TEENSY_SYNTH_LOGR_H
