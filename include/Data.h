// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_DATA_H_
#define STATS_INCLUDE_DATA_H_

#include <fstream>
#include <string>
#include <vector>

namespace STATS {

struct dataPoint {
    double x;
    double y;
    double yErrLow;
    double yErrHigh;

    friend std::ostream& operator<<(std::ostream& stream, const dataPoint& p) {
        stream << "(" << p.x << "," << p.y << "," << p.yErrLow << "," << p.yErrHigh << ")";
        return stream;
    }
};

class Data {
   public:
    Data(double xmin, double xmax) : m_xmin(xmin), m_xmax(xmax) {}
    virtual ~Data() = default;
    void loadDatafile(const std::string& filename);

   public:
    const std::vector<dataPoint>& table = m_table;

   protected:
    std::vector<dataPoint> m_table;
    double m_xmin;
    double m_xmax;

   protected:
    void append(const std::string& filename);
};

}  // namespace STATS

#endif  // STATS_INCLUDE_DATA_H_
