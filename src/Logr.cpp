//
// Created by mjrsk on 9/24/2021.
//
#include "Logr.h"

void Logr::line(const char *line) {
    LOG.println(line);
}

void Logr::info(const char *line) {
#ifdef LOG_INFO
    LOG.println(line);
#endif
}

void Logr::debug(const char *line) {
#ifdef LOG_DEBUG
    LOG.println(line);
#endif
}

void Logr::error(const char *line) {
#ifdef LOG_ERROR
    LOG.println(line);
#endif
}
