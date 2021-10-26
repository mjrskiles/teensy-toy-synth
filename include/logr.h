//
// Created by mjrsk on 9/24/2021.
//

#ifndef TEENSY_SYNTH_LOGR_H
#define TEENSY_SYNTH_LOGR_H

#include <Arduino.h>
#include <utils/singleton.h>

#define LOGR_LOG Serial
#define LOG_INFO Serial
#define LOG_DEBUG Serial
#define LOG_ERROR Serial

class Logr {
public:
    static Logr& getInstance() {
        static Logr instance;
        return instance;
    }
    static void line(const char * line);
    static void info(const char * line);
    static void debug(const char * line);
    static void error(const char * line);
private:
    Logr() {}
    Logr(Logr const&); // Don't Implement.
    void operator=(Logr const&); // Don't implement
};

#endif //TEENSY_SYNTH_LOGR_H
