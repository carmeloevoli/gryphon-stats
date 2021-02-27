// Copyright CRPROPA - https://crpropa.desy.de/
#ifndef STATS_INCLUDE_PROGRESSBAR_H_
#define STATS_INCLUDE_PROGRESSBAR_H_

#include <ctime>
#include <memory>
#include <mutex>
#include <string>

namespace STATS {

class ProgressBar {
   private:
    unsigned long m_steps;
    unsigned long m_currentCount;
    unsigned long m_maxbarLength;
    unsigned long m_nextStep;
    unsigned long m_updateSteps;
    time_t m_startTime;
    std::string m_stringTmpl;
    std::string m_arrow;
    bool m_mutexSet;
    std::shared_ptr<std::mutex> m_mutex;

   public:
    ProgressBar(unsigned long steps = 0, unsigned long updateSteps = 100);
    void setMutex(std::shared_ptr<std::mutex> mutex);
    void start(const std::string &title);
    void update();
    void setPosition(unsigned long position);
    void setError();
};

}  // namespace STATS

#endif  // STATS_INCLUDE_PROGRESSBAR_H_
