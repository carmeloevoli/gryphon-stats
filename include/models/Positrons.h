// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_MODELS_POSITRONS_H_
#define STATS_INCLUDE_MODELS_POSITRONS_H_

#include <memory>

#include "Model.h"
#include "Particle.h"
#include "models/Secondary.h"

namespace STATS {

class Positrons : public Model {
   public:
    Positrons(const std::string initFilename, const int& nSample,
              std::shared_ptr<SecondaryPositrons> secondary);
    virtual ~Positrons() = default;

   protected:
    std::vector<double> m_E;
    Sample m_positronSample;
    std::vector<double> m_median;
    std::vector<double> m_mad;
    std::vector<double> m_mean;
    std::vector<double> m_sdev;
    std::vector<double> m_p95_low;
    std::vector<double> m_p95_high;
    std::shared_ptr<SecondaryPositrons> m_secondary;

   protected:
    void init();
    std::vector<double> computeMeasures(const std::vector<double>& v);

   public:
    double get(double x, std::vector<double> params);
    void print(std::string filename);
    std::vector<double> getInterpolatedFlux(const double& E) const;
};

}  // namespace STATS

#endif  // #define STATS_INCLUDE_MODELS_POSITRONPWNE_H_
