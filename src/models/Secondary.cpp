#include "models/Secondary.h"

#include <plog/Log.h>

#include <fstream>

#include "Utilities.h"

namespace STATS {

SecondaryPositrons::SecondaryPositrons(const std::string filename) {
    if (!UTILS::fileExists(filename)) {
        throw std::runtime_error("file input for SecondaryPositrons does not exist.");
    } else {
        init(filename);
    }
}

void SecondaryPositrons::init(const std::string filename) {
    const int maxNCharInLine = 512;
    std::fstream fileToRead(filename.c_str());
    for (int i = 0; i < 1; ++i) fileToRead.ignore(maxNCharInLine, '\n');
    double E_i, electrons_i, positrons_i;
    while (!fileToRead.eof()) {
        fileToRead >> E_i >> electrons_i >> positrons_i;
        if (!fileToRead.eof()) {
            m_E.push_back(E_i);
            m_flux.push_back(positrons_i);
        }
    }
    LOGI << "read energy vector between min: " << m_E.front() << " and max: " << m_E.back();
}

double SecondaryPositrons::get(double x) {
    const double E = x;
    return m_efficiency * UTILS::LinearInterpolatorLog(m_E, m_flux, E);
}

double SecondaryPositrons::get(double x, std::vector<double> params) {
    const double E = x;
    const double efficiency = params[0];
    return efficiency * UTILS::LinearInterpolatorLog(m_E, m_flux, E);
}

void SecondaryPositrons::print(std::string filename) {
    // std::ofstream outfile(filename.c_str());
    // if (outfile.is_open()) {
    //     outfile << std::scientific << std::setprecision(4);
    //     outfile << "# E - median - mad - mean - sdev - %2.5 - %97.5\n";
    //     for (size_t i = 0; i < m_E.size(); ++i) {
    //         outfile << m_E.at(i) << "\t";
    //         outfile << m_efficiency * m_median.at(i) << "\t";
    //         outfile << m_efficiency * m_mad.at(i) << "\t";
    //         outfile << m_efficiency * m_mean.at(i) << "\t";
    //         outfile << m_efficiency * m_sdev.at(i) << "\t";
    //         outfile << m_efficiency * m_p95_low.at(i) << "\t";
    //         outfile << m_efficiency * m_p95_high.at(i) << "\t";
    //         outfile << "\n";
    //     }
    //     outfile.close();
    // }
    // LOGI << "saved results on file " << filename;
}

}  // namespace STATS