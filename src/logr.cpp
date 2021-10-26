//
// Created by mjrsk on 9/24/2021.
//
#include "logr.h"

void Logr::line(const char *line) {
    LOGR_LOG.println(line);
}

void Logr::info(const char *line) {
#ifdef LOG_INFO
    LOGR_LOG.println(line);
#endif
}

void Logr::debug(const char *line) {
#ifdef LOG_DEBUG
    LOGR_LOG.println(line);
#endif
}

void Logr::error(const char *line) {
#ifdef LOG_ERROR
    LOGR_LOG.println(line);
#endif
}


