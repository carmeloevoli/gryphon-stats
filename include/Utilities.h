// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef LIBS_STATS_INCLUDE_UTILITIES_H_
#define LIBS_STATS_INCLUDE_UTILITIES_H_

#include <string>

namespace UTILS {

// const int max_num_of_char_in_a_line = 512;

bool fileExists(const std::string& name);
int countLines(const std::string& filename);

// inline double pow2(const double& x) { return x * x; }

}  // namespace UTILS

#endif  // LIBS_STATS_INCLUDE_UTILITIES_H_
