//
// Created by mjrsk on 9/24/2021.
//

#ifndef TEENSY_SYNTH_LOGR_H
#define TEENSY_SYNTH_LOGR_H

#include "logr_config.h"

enum LogLevel : int {
    INFO,
    DEBUG,
    ERROR
};

static const char *log_level_names[3] {"Info", "Debug", "Error"};


class Logr {
public:
    static Logr& getInstance() {
        static Logr instance;
        return instance;
    }
    static void line(const char * line);
    static void info(const char * line, ...);
    static void debug(const char * line, ...);
    static void error(const char * line, ...);
private:
    Logr() {}
    Logr(Logr const&); // Don't Implement.
    void operator=(Logr const&); // Don't implement
    static void _print(LogLevel logLevel, const char *format, ...);
};

#endif //TEENSY_SYNTH_LOGR_H
