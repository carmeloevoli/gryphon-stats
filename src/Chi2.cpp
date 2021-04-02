// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include "Chi2.h"

#include <plog/Log.h>

#include <cmath>

namespace STATS {

Chi2::Chi2(const std::shared_ptr<Model> model, const std::shared_ptr<Data> data)
    : m_model(model), m_data(data) {}

double Chi2::run(double x_min, double x_max) const {
    double min_chi2 = 1e10;
    double best_efficiency = -1;
    for (double eps = x_min; eps <= x_max; eps *= 1.001) {
        const auto chi2 = computeChi2(eps);
        if (chi2 < min_chi2) {
            min_chi2 = chi2;
            best_efficiency = eps;
        }
    }
    LOGI << "> 🚩 found min chi2: " << min_chi2 << " with efficiency: " << best_efficiency;
    return best_efficiency;
}

double Chi2::computeChi2(double eps) const {
    double value = 0.0;
    size_t ndata = 0;
    for (auto it = m_data->table.begin(); it != m_data->table.end(); it++) {
        const auto yModel = m_model->get(it->x, {eps});
        auto deltaChi2 = std::pow(yModel - it->y, 2);
        deltaChi2 /= (yModel < it->y) ? std::pow(it->yErrLow, 2) : std::pow(it->yErrHigh, 2);
        value += deltaChi2;
        ndata++;
    }
    return value / (double)(ndata - 1);
}

}  // namespace STATS