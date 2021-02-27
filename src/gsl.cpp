#include <gsl/gsl_statistics.h>
#include <gsl/gsl_vector.h>

#include <vector>

namespace GSL {

double median(const std::vector<double>& data) {
    const int size = data.size();
    auto gsl_v = gsl_vector_const_view_array(&data[0], size);
    return gsl_stats_median(gsl_v.vector.data, 1, size);
}

double mean(const std::vector<double>& data) {
    const int size = data.size();
    auto gsl_v = gsl_vector_const_view_array(&data[0], size);
    return gsl_stats_mean(gsl_v.vector.data, 1, size);
}

double mad(const std::vector<double>& data) {
    const int size = data.size();
    auto gsl_v = gsl_vector_const_view_array(&data[0], size);
    double* work = new double[size];
    const auto value = gsl_stats_mad(gsl_v.vector.data, 1, size, work);
    delete[] work;
    return value;
}

double sdev(const std::vector<double>& data) {
    const int size = data.size();
    auto gsl_v = gsl_vector_const_view_array(&data[0], size);
    return gsl_stats_sd(gsl_v.vector.data, 1, size);
}

}  // namespace GSL