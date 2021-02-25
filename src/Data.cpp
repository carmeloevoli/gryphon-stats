// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include "Data.h"

#include <plog/Log.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Utilities.h"

namespace STATS {

void Data::loadDatafile(const std::string& filename) {
    if (UTILS::fileExists(filename)) {
        append(filename);
    } else {
        throw std::runtime_error("data file does not exists.");
    }
}

void Data::append(const std::string& filename) {
    const int maxNCharInLine = 512;
    std::ifstream fileToRead(filename.c_str());
    int counter = 0;
    if (fileToRead.is_open()) {
        for (int i = 0; i < 7; ++i) fileToRead.ignore(maxNCharInLine, '\n');
        double values[6];
        while (!fileToRead.eof()) {
            for (int j = 0; j < 6; ++j) fileToRead >> values[j];  // TODO check this
            dataPoint point;
            point.x = values[0];
            point.y = values[1];
            point.yErrLow = values[2];
            point.yErrHigh = values[3];
            if (fileToRead.good()) {
                m_table.push_back(point);
                counter++;
            }
        }
    }
    LOGI << "read " << counter << " data from " << filename;
    fileToRead.close();
}

}  // namespace STATS
