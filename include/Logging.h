#ifndef INCLUDE_LOGGING_H_
#define INCLUDE_LOGGING_H_

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/CsvFormatter.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

void logStartupInformation() {
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
#ifdef DEBUG
    plog::init(plog::debug, &consoleAppender);
#else
    plog::init(plog::info, &consoleAppender);
#endif
    LOGI << "Welcome to GRYPHON-STATS";
}

#endif  // INCLUDE_LOGGING_H_