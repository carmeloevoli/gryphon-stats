// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_GSL_H_
#define STATS_INCLUDE_GSL_H_

#include <vector>

namespace GSL {

double median(const std::vector<double>& data);
double mean(const std::vector<double>& data);
double mad(const std::vector<double>& data);
double sdev(const std::vector<double>& data);
double spline(const std::vector<double>& x, const std::vector<double>& y, double x_new);

}  // namespace GSL

#endif  // STATS_INCLUDE_GSL_H_