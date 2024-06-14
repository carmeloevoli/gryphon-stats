// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include "Particle.h"

#include <plog/Log.h>

#include <cassert>
#include <fstream>
#include <iostream>

#include "Utilities.h"

namespace STATS {

Particle::Particle(const std::string& initFilename, int sampleSize, bool doFlux)
    : m_doFlux(doFlux) {
    LOGI << "reading sample from " << initFilename;
    LOGI << "expected sample size is " << sampleSize;
    existsFile0(initFilename);
    const auto nRows = UTILS::countLines(initFilename + "_0.txt") - 1;
    m_E = loadEnergyVector(initFilename, nRows);
    m_sample = loadSample(initFilename, sampleSize, nRows);
}

bool Particle::existsFile0(const std::string& initFilename) const {
    const std::string filename = initFilename + "_0.txt";
    if (!UTILS::fileExists(filename)) {
        throw std::runtime_error("file 0 must exists.");
    }
    return true;
}

std::vector<double> Particle::loadEnergyVector(const std::string& initFilename, int nRows) const {
    const int maxNCharInLine = 512;
    std::string filename_0 = initFilename + "_0.txt";
    std::fstream fileToRead(filename_0.c_str());
    std::vector<double> E;
    for (int i = 0; i < 1; ++i) fileToRead.ignore(maxNCharInLine, '\n');
    double E_i, flux_i, flux_max_i;
    while (!fileToRead.eof()) {
        fileToRead >> E_i >> flux_i >> flux_max_i;
        if (!fileToRead.eof()) {
            E.push_back(E_i);
        }
    }
    if (E.size() != nRows) throw std::runtime_error("incorrect size in readEnergyVector.");
    LOGI << "read energy vector between min: " << E.front() << " and max: " << E.back();
    return E;
}

std::vector<double> Particle::loadFluxVector(const std::string& filename, int nRows) const {
    const int maxNCharInLine = 512;
    std::vector<double> flux;
    std::fstream fileToRead(filename.c_str());
    for (int i = 0; i < 1; ++i) fileToRead.ignore(maxNCharInLine, '\n');
    double E_i, flux_i, flux_max_i;
    for (size_t j = 0; j < nRows; ++j) {
        fileToRead >> E_i >> flux_i >> flux_max_i;
        if (E_i != m_E.at(j)) {
            std::cout << filename << "\n";
            throw std::runtime_error("the energy vector is not the same for all files.");
        }
        if (m_doFlux)
            flux.push_back(flux_i);
        else
            flux.push_back(flux_max_i);
    }
    assert(flux.size() == m_E.size());
    return flux;
}

Sample Particle::loadSample(const std::string& initFilename, int sampleSize, int nRows) {
    Sample sample;
    for (size_t i = 0; i < sampleSize; ++i) {
        const std::string filename = initFilename + "_" + std::to_string(i) + ".txt";
        auto flux = loadFluxVector(filename, nRows);
        sample.insert(std::pair<int, std::vector<double> >(i, flux));
    }
    assert(sample.size() == sampleSize);
    LOGI << "loaded a sample of " << sample.size() << " realizations";
    return sample;
}

}  // namespace STATS
