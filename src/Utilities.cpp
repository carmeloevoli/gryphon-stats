// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include "Utilities.h"

#include <cmath>
#include <fstream>
#include <string>

namespace UTILS {

int countLines(const std::string& filename) {
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(filename.c_str());
    while (std::getline(myfile, line)) ++number_of_lines;
    return number_of_lines;
}

bool fileExists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

double LinearInterpolator(const std::vector<double>& x, const std::vector<double>& y,
                          const double& x_new) {
    if (x_new < x.front() || x_new > x.back())
        throw std::invalid_argument("x_new out of vector range in LinearInterpolator");
    size_t const i = std::lower_bound(x.begin(), x.end(), x_new) - x.begin();
    const auto t = (x_new - x.at(i - 1)) / (x.at(i) - x.at(i - 1));
    return y.at(i - 1) * (1. - t) + y.at(i) * t;
}

double LinearInterpolatorLog(const std::vector<double>& x, const std::vector<double>& y,
                             const double& x_new) {  // TODO pass to GSL?
    if (x_new < x.front() || x_new > x.back())
        throw std::invalid_argument("x_new out of vector range in LinearInterpolatorLog");
    size_t const i = std::lower_bound(x.begin(), x.end(), x_new) - x.begin();
    double t = std::log(x_new) - std::log(x.at(i));
    t /= std::log(x.at(i + 1)) - std::log(x.at(i));
    double v = std::log(y.at(i)) * (1. - t) + std::log(y.at(i + 1)) * t;
    return std::exp(v);
}

}  // namespace UTILS
