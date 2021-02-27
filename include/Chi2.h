// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_CHI2_H_
#define STATS_INCLUDE_CHI2_H_

#include <memory>
#include <string>

#include "Data.h"
#include "Model.h"

namespace STATS {

class Chi2 {
   public:
    Chi2(const std::shared_ptr<Model> model, const std::shared_ptr<Data> data);
    virtual ~Chi2() = default;

    // void buildProtons(const std::string& initFilename, int N);
    // void buildChi2(const std::string& dataFilename);
    double run(double x_min, double x_max) const;
    // void print(const std::string& filename, double efficiency) const;

   protected:
    std::shared_ptr<Model> m_model;
    std::shared_ptr<Data> m_data;

   protected:
    double computeChi2(double eps) const;
};

}  // namespace STATS

#endif  // STATS_INCLUDE_CHI2_H_
