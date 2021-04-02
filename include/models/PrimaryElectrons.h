// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_MODELS_PRIMARYELECTRONS_H_
#define STATS_INCLUDE_MODELS_PRIMARYELECTRONS_H_

#include <memory>
#include <string>

#include "Model.h"
#include "Particle.h"

namespace STATS {

class PrimaryElectrons : public Model {
   protected:
    std::vector<double> m_E_pwn;
    std::vector<double> m_E_snr;
    Sample m_pwnSample;
    Sample m_snrSample;
    double m_efficiencyPWN;

    std::vector<double> m_median;
    std::vector<double> m_mad;
    std::vector<double> m_mean;
    std::vector<double> m_sdev;

    std::vector<double> m_median_all;
    std::vector<double> m_mad_all;
    std::vector<double> m_mean_all;
    std::vector<double> m_sdev_all;

   protected:
    void init(double efficiency_snr);
    double getMedian(double efficiency_snr, size_t i);

    //     std::vector<double> computeMeasures(const std::vector<double>& v);

   public:
    PrimaryElectrons(const std::string initFilename_snr, const std::string initFilename_pwn,
                     double efficiency_pwn, const int& nSample);
    virtual ~PrimaryElectrons() = default;

    double get(double x, std::vector<double> params);
    void print(std::string filename);
    // std::vector<double> getInterpolatedFlux(const double& E) const;
};

}  // namespace STATS

#endif  // #define STATS_INCLUDE_MODELS_PRIMARYELECTRONS_H_
