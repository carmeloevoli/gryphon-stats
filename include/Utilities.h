// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_UTILITIES_H_
#define STATS_INCLUDE_UTILITIES_H_

#include <string>
#include <vector>

namespace UTILS {

// const int max_num_of_char_in_a_line = 512;

bool fileExists(const std::string& name);
int countLines(const std::string& filename);
double LinearInterpolator(const std::vector<double>& x, const std::vector<double>& y,
                          const double& x_new);
double LinearInterpolatorLog(const std::vector<double>& x, const std::vector<double>& y,
                             const double& x_new);

// inline double pow2(const double& x) { return x * x; }

}  // namespace UTILS

#endif  // STATS_INCLUDE_UTILITIES_H_
