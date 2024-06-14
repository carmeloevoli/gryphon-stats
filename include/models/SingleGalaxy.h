// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_MODELS_SINGLEGALAXY_H_
#define STATS_INCLUDE_MODELS_SINGLEGALAXY_H_

#include <memory>

#include "Model.h"

namespace STATS {

class SinglePositrons : public Model {
   protected:
    std::vector<double> m_E;
    std::vector<double> m_flux;

   protected:
    void init(const std::string& filename);

   public:
    SinglePositrons(const std::string filename);
    virtual ~SinglePositrons() = default;

    double get(double x, std::vector<double> params);
    double get(double x);
    void print(std::string filename);
};

class SingleLeptons : public Model {
   protected:
    std::vector<double> m_E;
    std::vector<double> m_flux;
    std::shared_ptr<SinglePositrons> m_positrons;

   protected:
    void init(const std::string& filename);

   public:
    SingleLeptons(const std::string filename, std::shared_ptr<SinglePositrons> positrons);
    virtual ~SingleLeptons() = default;

    double get(double x, std::vector<double> params);
    void print(std::string filename);
};

}  // namespace STATS

#endif  // STATS_INCLUDE_MODELS_SINGLEGALAXY_H_
