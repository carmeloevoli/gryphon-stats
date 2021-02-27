// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_MODEL_H_
#define STATS_INCLUDE_MODEL_H_

#include <string>
#include <vector>

class Model {
   protected:
    double m_efficiency = 1;

   public:
    Model() {}
    virtual ~Model() = default;
    void setEfficiency(const double& e) { m_efficiency = e; }
    virtual double get(double x, std::vector<double> params) const = 0;
    virtual void print(std::string filename) const = 0;
};

#endif  // STATS_INCLUDE_MODEL_H_