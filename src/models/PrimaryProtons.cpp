#include "models/PrimaryProtons.h"

#include <plog/Log.h>

#include <fstream>
#include <iomanip>
#include <string>

#include "gsl.h"
#include "utilities.h"

namespace STATS {

PrimaryProtons::PrimaryProtons(const std::string initFilename, const int& nSample) {
    auto protons = std::make_shared<Particle>(initFilename, nSample);
    m_E = protons->getE();
    m_protonsSample = protons->getSample();
    m_median.resize(m_E.size());
    m_mad.resize(m_E.size());
    m_mean.resize(m_E.size());
    m_sdev.resize(m_E.size());
    m_p95_low.resize(m_E.size());
    m_p95_high.resize(m_E.size());
    init();
}

void PrimaryProtons::init() {
    for (int i = 0; i < m_E.size(); ++i) {
        std::vector<double> v;
        for (const auto realization : m_protonsSample) v.push_back(realization.second.at(i));
        m_median.at(i) = GSL::median(v);
        m_mad.at(i) = GSL::mad(v);
        m_mean.at(i) = GSL::mean(v);
        m_sdev.at(i) = GSL::sdev(v);
        m_p95_low.at(i) = GSL::percentile(v, 2.5 / 100.);
        m_p95_high.at(i) = GSL::percentile(v, 97.5 / 100.);
    }
}

double PrimaryProtons::get(double x, std::vector<double> params) {
    const double E = x;
    const double efficiency = params[0];
    return efficiency * UTILS::LinearInterpolatorLog(m_E, m_median, E);
}

void PrimaryProtons::print(std::string filename) {
    std::ofstream outfile(filename.c_str());
    if (outfile.is_open()) {
        outfile << std::scientific << std::setprecision(4);
        outfile << "# E - median - mad - mean - sdev - %2.5 - %97.5\n";
        for (size_t i = 0; i < m_E.size(); ++i) {
            outfile << m_E.at(i) << "\t";
            outfile << m_efficiency * m_median.at(i) << "\t";
            outfile << m_efficiency * m_mad.at(i) << "\t";
            outfile << m_efficiency * m_mean.at(i) << "\t";
            outfile << m_efficiency * m_sdev.at(i) << "\t";
            outfile << m_efficiency * m_p95_low.at(i) << "\t";
            outfile << m_efficiency * m_p95_high.at(i) << "\t";
            outfile << "\n";
        }
        outfile.close();
    }
    LOGI << "saved results on file " << filename;
}

std::vector<double> PrimaryProtons::getInterpolatedFlux(const double& E) const {
    const auto size = m_protonsSample.size();
    std::vector<double> output;
    for (const auto realization : m_protonsSample) {
        const auto flux = realization.second;
        const auto value = UTILS::LinearInterpolatorLog(m_E, flux, E);
        output.push_back(m_efficiency * value);
    }
    return output;
}

}  // namespace STATS