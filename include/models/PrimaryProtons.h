// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_MODELS_PRIMARYPROTONS_H_
#define STATS_INCLUDE_MODELS_PRIMARYPROTONS_H_

#include <memory>

#include "Model.h"
#include "Particle.h"

namespace STATS {

class PrimaryProtons : public Model {
   private:
    std::vector<double> m_E;
    Sample m_protonsSample;
    std::vector<double> m_median;
    std::vector<double> m_mad;
    std::vector<double> m_mean;
    std::vector<double> m_sdev;

   private:
    void init();
    std::vector<double> computeMeasures(const std::vector<double>& v);

   public:
    PrimaryProtons(const std::string initFilename, const int& nSample);
    virtual ~PrimaryProtons() = default;

    double get(double x, std::vector<double> params) const;
    void print(std::string filename) const;
    std::vector<double> getInterpolatedFlux(const double& E) const;
};

}  // namespace STATS

#endif  // #define STATS_INCLUDE_MODELS_PRIMARYPROTONS_H_
