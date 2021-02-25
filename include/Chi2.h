// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef LIBS_STATS_INCLUDE_TFITPROTONS_H_
#define LIBS_STATS_INCLUDE_TFITPROTONS_H_

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
    double m_xMin = 0;  // TODO init this
    double m_xMax = 1;
    // std::pair<double, double> m_E_range;

   protected:
    double computeChi2(double eps) const;
};

}  // namespace STATS

#endif  // LIBS_STATS_INCLUDE_TFITPROTONS_H_
