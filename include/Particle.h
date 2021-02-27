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

    // std::vector<measures> m_flux;

   protected:
    bool existsFile0(const std::string& initFilename) const;
    std::vector<double> loadEnergyVector(const std::string& initFilename, int nRows) const;
    std::vector<double> loadFluxVector(const std::string& filename, int nRows) const;
    Sample loadSample(const std::string& initFilename, int nModels, int nRows);

   public:
    explicit Particle(const std::string& initFilename, int sampleSize);
    virtual ~Particle() = default;

    const std::vector<double>& getE() const { return m_E; }
    const Sample& getSample() const { return m_sample; }

    // void compute_measures();
    // const size_t get_E_size() const { return m_E.size(); }
    // const size_t get_sample_size() const { return m_sample.size(); }
    // const double get_median(size_t i) const { return m_flux.at(i).median; }
    // const double get_mean(size_t i) const { return m_flux.at(i).mean; }
    // const double get_stdev(size_t i) const { return m_flux.at(i).stdev; }
    // const double get_mad(size_t i) const { return m_flux.at(i).mad; }
    // const std::vector<double> get_flux_array(size_t alpha) const {
    //     return m_sample.find(alpha)->second;
    // }
};

}  // namespace STATS

#endif  // STATS_INCLUDE_PARTICLE_H_
