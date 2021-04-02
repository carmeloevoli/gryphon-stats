#ifndef STATS_INCLUDE_LOGGING_H_
#define STATS_INCLUDE_LOGGING_H_

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/CsvFormatter.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

enum {
    // default is 0
    kConsole = 1,
    kFile
};

void logStartupInformation() {
    static plog::RollingFileAppender<plog::CsvFormatter> fileAppender("gryphon-stats.csv", 8000, 3);
    plog::init<kFile>(plog::debug, &fileAppender);

    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
#ifdef DEBUG
    plog::init<kConsole>(plog::debug, &consoleAppender);
#else
    plog::init<kConsole>(plog::info, &consoleAppender);
#endif
    plog::init(plog::debug, plog::get<kConsole>()).addAppender(plog::get<kFile>());
    LOGI << "Welcome to GRYPHON-STATS";
}

#endif  // INCLUDE_LOGGING_H_
