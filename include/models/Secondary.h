// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_MODELS_SECONDARY_H_
#define STATS_INCLUDE_MODELS_SECONDARY_H_

#include <memory>

#include "Model.h"

namespace STATS {

class SecondaryPositrons : public Model {
   protected:
    std::vector<double> m_E;
    std::vector<double> m_flux;

   protected:
    void init(const std::string filename);

   public:
    SecondaryPositrons(const std::string filename);
    virtual ~SecondaryPositrons() = default;

    double get(double x, std::vector<double> params);
    double get(double x);
    void print(std::string filename);
};

}  // namespace STATS

#endif  // #define STATS_INCLUDE_MODELS_SECONDARY_H_
