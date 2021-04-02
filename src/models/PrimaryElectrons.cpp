#include "models/PrimaryElectrons.h"

#include <plog/Log.h>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

#include "gsl.h"
#include "utilities.h"

namespace STATS {

PrimaryElectrons::PrimaryElectrons(const std::string initFilename_snr,
                                   const std::string initFilename_pwn, double efficiency_pwn,
                                   const int& nSample) {
    auto pwn = std::make_shared<Particle>(initFilename_pwn, nSample);
    m_E_pwn = pwn->getE();
    m_pwnSample = pwn->getSample();
    auto snr = std::make_shared<Particle>(initFilename_snr, nSample);
    m_E_snr = snr->getE();
    m_snrSample = snr->getSample();
    m_efficiencyPWN = efficiency_pwn;
    auto size = m_E_snr.size();
    m_median.resize(size);
    m_mad.resize(size);
    m_mean.resize(size);
    m_sdev.resize(size);
    m_median_all.resize(size);
    m_mad_all.resize(size);
    m_mean_all.resize(size);
    m_sdev_all.resize(size);
}

double PrimaryElectrons::getMedian(double efficiency_snr, size_t i) {
    int size = m_snrSample.size();
    std::vector<double> v;
    for (int j = 0; j < size; ++j) {
        auto value = efficiency_snr * m_snrSample[j].at(i) + m_efficiencyPWN * m_pwnSample[j].at(i);
        v.push_back(value);
    }
    return GSL::median(v);
}

void PrimaryElectrons::init(double efficiency_snr) {
    int size = m_snrSample.size();
    for (int i = 0; i < m_E_snr.size(); ++i) {
        std::vector<double> v;
        for (int j = 0; j < size; ++j) {
            auto value =
                efficiency_snr * m_snrSample[j].at(i) + m_efficiencyPWN * m_pwnSample[j].at(i);
            v.push_back(value);
        }
        m_median.at(i) = GSL::median(v);
        m_mad.at(i) = GSL::mad(v);
        m_mean.at(i) = GSL::mean(v);
        m_sdev.at(i) = GSL::sdev(v);
    }

    for (int i = 0; i < m_E_snr.size(); ++i) {
        std::vector<double> v;
        for (int j = 0; j < size; ++j) {
            auto value =
                efficiency_snr * m_snrSample[j].at(i) + 2. * m_efficiencyPWN * m_pwnSample[j].at(i);
            v.push_back(value);
        }
        m_median_all.at(i) = GSL::median(v);
        m_mad_all.at(i) = GSL::mad(v);
        m_mean_all.at(i) = GSL::mean(v);
        m_sdev_all.at(i) = GSL::sdev(v);
    }
}

double PrimaryElectrons::get(double x, std::vector<double> params) {
    const double E = x;
    const double efficiency = params[0];

    if (E < m_E_snr.front() || E > m_E_snr.back())
        throw std::invalid_argument("E out of vector range in get");

    size_t const i = std::lower_bound(m_E_snr.begin(), m_E_snr.end(), E) - m_E_snr.begin();

    double t = std::log(E) - std::log(m_E_snr.at(i));
    t /= std::log(m_E_snr.at(i + 1)) - std::log(m_E_snr.at(i));

    double y_i = getMedian(efficiency, i);
    double y_iNext = getMedian(efficiency, i + 1);

    double logv = std::log(y_i) * (1. - t) + std::log(y_iNext) * t;
    return std::exp(logv);
}

void PrimaryElectrons::print(std::string filename) {
    init(m_efficiency);
    std::ofstream outfile(filename.c_str());
    if (outfile.is_open()) {
        outfile << std::scientific << std::setprecision(4);
        outfile << "# E - median - mad - mean - sdev\n";
        for (size_t i = 0; i < m_E_snr.size(); ++i) {
            outfile << m_E_snr.at(i) << "\t";
            outfile << m_median.at(i) << "\t";
            outfile << m_mad.at(i) << "\t";
            outfile << m_mean.at(i) << "\t";
            outfile << m_sdev.at(i) << "\t";
            outfile << m_median_all.at(i) << "\t";
            outfile << m_mad_all.at(i) << "\t";
            outfile << m_mean_all.at(i) << "\t";
            outfile << m_sdev_all.at(i) << "\t";
            outfile << "\n";
        }
        outfile.close();
    }
    LOGI << "saved results on file " << filename;
}

// std::vector<double> PrimaryProtons::getInterpolatedFlux(const double& E) const {
//     const auto size = m_protonsSample.size();
//     std::vector<double> output;
//     for (const auto realization : m_protonsSample) {
//         const auto flux = realization.second;
//         const auto value = UTILS::LinearInterpolatorLog(m_E, flux, E);
//         output.push_back(m_efficiency * value);
//     }
//     return output;
// }

}  // namespace STATS