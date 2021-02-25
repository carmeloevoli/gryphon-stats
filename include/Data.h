// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef LIBS_STATS_INCLUDE_TDATA_H_
#define LIBS_STATS_INCLUDE_TDATA_H_

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
    Data() {}
    virtual ~Data() = default;
    void loadDatafile(const std::string& filename);

   public:
    const std::vector<dataPoint>& table = m_table;

   protected:
    std::vector<dataPoint> m_table;

   protected:
    void append(const std::string& filename);
};

}  // namespace STATS

#endif  // LIBS_STATS_INCLUDE_TDATA_H_
