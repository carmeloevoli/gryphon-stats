#include <gsl/gsl_errno.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_spline.h>
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

double percentile(const std::vector<double>& data, double percentile) {
    auto size = data.size();
    std::vector<double> sorted_vector;
    copy(data.begin(), data.end(), back_inserter(sorted_vector));
    gsl_sort(&sorted_vector[0], 1, size);
    return gsl_stats_quantile_from_sorted_data(&sorted_vector[0], 1, size, percentile);
}

double spline(const std::vector<double>& x, const std::vector<double>& y, double x_new) {
    const auto size = x.size();
    auto gsl_x = gsl_vector_const_view_array(&x[0], size);
    auto gsl_y = gsl_vector_const_view_array(&y[0], size);
    gsl_interp_accel* acc = gsl_interp_accel_alloc();
    gsl_spline* spline = gsl_spline_alloc(gsl_interp_cspline, size);
    gsl_spline_init(spline, gsl_x.vector.data, gsl_y.vector.data, size);
    auto value = gsl_spline_eval(spline, x_new, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return value;
}

}  // namespace GSL