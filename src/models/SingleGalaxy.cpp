#include "models/SingleGalaxy.h"

#include <plog/Log.h>

#include <fstream>
#include <iomanip>
#include <string>

#include "utilities.h"

namespace STATS {

SinglePositrons::SinglePositrons(const std::string filename) {
    if (!UTILS::fileExists(filename)) {
        throw std::runtime_error("file input for SinglePositrons does not exist.");
    } else {
        init(filename);
    }
}

void SinglePositrons::init(const std::string& filename) {
    const int maxNCharInLine = 512;
    std::fstream fileToRead(filename.c_str());
    for (int i = 0; i < 1; ++i) fileToRead.ignore(maxNCharInLine, '\n');
    double E_i, flux_i, flux_max_i;
    while (!fileToRead.eof()) {
        fileToRead >> E_i >> flux_i >> flux_max_i;
        if (!fileToRead.eof()) {
            m_E.push_back(E_i);
            m_flux.push_back(flux_i);
        }
    }
    LOGI << "read energy vector between min: " << m_E.front() << " and max: " << m_E.back();
}

double SinglePositrons::get(double x) {
    const double E = x;
    return m_efficiency * UTILS::LinearInterpolatorLog(m_E, m_flux, E);
}

double SinglePositrons::get(double x, std::vector<double> params) {
    const double E = x;
    const double efficiency = params[0];
    return efficiency * UTILS::LinearInterpolatorLog(m_E, m_flux, E);
}

void SinglePositrons::print(std::string filename) {
    std::ofstream outfile(filename.c_str());
    if (outfile.is_open()) {
        outfile << std::scientific << std::setprecision(4);
        outfile << "# E - flux\n";
        for (size_t i = 0; i < m_E.size(); ++i) {
            outfile << m_E.at(i) << "\t";
            outfile << m_efficiency * m_flux.at(i) << "\t";
            outfile << "\n";
        }
        outfile.close();
    }
    LOGI << "saved results on file " << filename;
}

//

SingleLeptons::SingleLeptons(const std::string filename, std::shared_ptr<SinglePositrons> positrons)
    : m_positrons(positrons) {
    if (!UTILS::fileExists(filename)) {
        throw std::runtime_error("file input for SinglePositrons does not exist.");
    } else {
        init(filename);
    }
}

void SingleLeptons::init(const std::string& filename) {
    const int maxNCharInLine = 512;
    std::fstream fileToRead(filename.c_str());
    for (int i = 0; i < 1; ++i) fileToRead.ignore(maxNCharInLine, '\n');
    double E_i, flux_i, flux_max_i;
    while (!fileToRead.eof()) {
        fileToRead >> E_i >> flux_i >> flux_max_i;
        if (!fileToRead.eof()) {
            m_E.push_back(E_i);
            m_flux.push_back(flux_i);
        }
    }
    LOGI << "read energy vector between min: " << m_E.front() << " and max: " << m_E.back();
}

double SingleLeptons::get(double x, std::vector<double> params) {
    const double E = x;
    const double efficiency = params[0];
    return efficiency * UTILS::LinearInterpolatorLog(m_E, m_flux, E) + 2.0 * m_positrons->get(x);
}

void SingleLeptons::print(std::string filename) {
    std::ofstream outfile(filename.c_str());
    if (outfile.is_open()) {
        outfile << std::scientific << std::setprecision(4);
        outfile << "# E - flux\n";
        for (size_t i = 0; i < m_E.size(); ++i) {
            outfile << m_E.at(i) << "\t";
            outfile << m_efficiency * m_flux.at(i) << "\t";
            outfile << "\n";
        }
        outfile.close();
    }
    LOGI << "saved results on file " << filename;
}

}  // namespace STATS