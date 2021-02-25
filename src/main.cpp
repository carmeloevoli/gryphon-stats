// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include <iostream>

#include "logging.h"

int main(int argc, char* argv[]) {
    logStartupInformation();
    try {
        LOGI << "hello";
    } catch (const std::exception& e) {
        LOGE << "exception caught with message: " << e.what();
    }
    return 0;
}