// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#ifndef STATS_INCLUDE_MODELS_POSITRONPWNE_H_
#define STATS_INCLUDE_MODELS_POSITRONPWNE_H_

#include <memory>

#include "Model.h"
#include "PrimaryProtons.h"

namespace STATS {

class PositronPWNe : public PrimaryProtons {
   public:
    PositronPWNe(const std::string initFilename, const int& nSample)
        : PrimaryProtons(initFilename, nSample) {}
    virtual ~PositronPWNe() = default;
};

}  // namespace STATS

#endif  // #define STATS_INCLUDE_MODELS_POSITRONPWNE_H_
