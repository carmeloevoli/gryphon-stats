// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_PARTICLE_H_
#define STATS_INCLUDE_PARTICLE_H_

#include <map>
#include <string>
#include <vector>

namespace STATS {

using Sample = std::map<size_t, std::vector<double> >;

class Particle {
   protected:
    std::vector<double> m_E;
    Sample m_sample;
    bool m_doFlux = true;

   protected:
    bool existsFile0(const std::string& initFilename) const;
    std::vector<double> loadEnergyVector(const std::string& initFilename, int nRows) const;
    std::vector<double> loadFluxVector(const std::string& filename, int nRows) const;
    Sample loadSample(const std::string& initFilename, int nModels, int nRows);

   public:
    explicit Particle(const std::string& initFilename, int sampleSize, bool doFlux = true);
    virtual ~Particle() = default;

    const std::vector<double>& getE() const { return m_E; }
    const Sample& getSample() const { return m_sample; }
    const int getSize() const { return m_sample.size(); }
};

}  // namespace STATS

#endif  // STATS_INCLUDE_PARTICLE_H_
