//
// Created by mjrsk on 9/24/2021.
//
#include "logr.h"


/*
 * https://stackoverflow.com/a/38224260
 */
void Logr::_print(LogLevel logLevel, const char *format, ...) {
    LOGR_LOG.printf("\nB~ [Logr %s] ", log_level_names[logLevel]);
    va_list argptr;
    va_start(argptr, format);
    LOGR_LOG.printf(format, argptr);
    va_end(argptr);
    LOGR_LOG.printf("\n");
}

void Logr::line(const char *line) {
    _print(INFO, line);
}

void Logr::info(const char *line, ...) {
#ifdef LOG_INFO
    va_list argptr;
    va_start(argptr, line);
    _print(INFO, line);
    va_end(argptr);
#endif
}

void Logr::debug(const char *line, ...) {
#ifdef LOG_DEBUG
    va_list argptr;
    va_start(argptr, line);
    _print(DEBUG, line);
    va_end(argptr);
#endif
}

void Logr::error(const char *line, ...) {
#ifdef LOG_ERROR
    va_list argptr;
    va_start(argptr, line);
    _print(ERROR, line);
    va_end(argptr);
#endif
}


