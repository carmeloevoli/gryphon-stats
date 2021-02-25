#include "include/ProgressBar.h"

#include <cstdio>
#include <iostream>
#include <utility>

namespace STATS {

ProgressBar::ProgressBar(unsigned long steps, unsigned long updateSteps)
    : m_steps(steps),
      m_currentCount(0),
      m_maxbarLength(10),
      m_updateSteps(updateSteps),
      m_nextStep(1),
      m_startTime(0),
      m_mutexSet(false) {
    if (m_updateSteps > m_steps) m_updateSteps = m_steps;
    m_arrow.append(">");
}

void ProgressBar::setMutex(std::shared_ptr<std::mutex> mutex) {
    m_mutex = std::move(mutex);
    m_mutexSet = true;
}

void ProgressBar::start(const std::string &title) {
    m_startTime = time(NULL);
    std::string s = ctime(&m_startTime);
    s.erase(s.end() - 1, s.end());
    m_stringTmpl = "  Started ";
    m_stringTmpl.append(s);
    m_stringTmpl.append(" : [%-10s] %3i%%    %s: %02i:%02i:%02i %s\r");
    std::cout << title << std::endl;
}

void ProgressBar::update() {
    if (m_mutexSet) {
        std::lock_guard<std::mutex> guard(*m_mutex);
        m_currentCount++;
        if (m_currentCount == m_nextStep || m_currentCount == m_steps || m_currentCount == 1000) {
            m_nextStep += long(m_steps / float(m_updateSteps));
            setPosition(m_currentCount);
        }
    } else {
        m_currentCount++;
        if (m_currentCount == m_nextStep || m_currentCount == m_steps || m_currentCount == 1000) {
            m_nextStep += long(m_steps / float(m_updateSteps));
            setPosition(m_currentCount);
        }
    }
}

void ProgressBar::setPosition(unsigned long position) {
    int percentage = int(100 * (position / float(m_steps)));
    time_t currentTime = time(NULL);
    if (position < m_steps) {
        if (m_arrow.size() <= (m_maxbarLength) * (position) / (m_steps)) m_arrow.insert(0, "=");
        time_t tElapsed = currentTime - m_startTime;
        float tToGo = (m_steps - position) * tElapsed / position;
        std::printf(m_stringTmpl.c_str(), m_arrow.c_str(), percentage, "Finish in",
                    int(tToGo / 3600), (int(tToGo) % 3600) / 60, int(tToGo) % 60, "");
        fflush(stdout);
    } else {
        float tElapsed = currentTime - m_startTime;
        std::string s = " - Finished at ";
        s.append(ctime(&currentTime));
        char fs[255];
        std::sprintf(fs, "%c[%d;%dm Finished %c[%dm", 27, 1, 32, 27, 0);
        std::printf(m_stringTmpl.c_str(), fs, 100, "Needed", int(tElapsed / 3600),
                    (int(tElapsed) % 3600) / 60, int(tElapsed) % 60, s.c_str());
    }
}

void ProgressBar::setError() {
    time_t currentTime = time(NULL);
    m_currentCount++;
    time_t tElapsed = currentTime - m_startTime;
    std::string s = " - Finished at ";
    s.append(ctime(&currentTime));
    char fs[255];
    std::sprintf(fs, "%c[%d;%dm  ERROR   %c[%dm", 27, 1, 31, 27, 0);
    std::printf(m_stringTmpl.c_str(), fs, m_currentCount, "Needed", int(tElapsed / 3600),
                (int(tElapsed) % 3600) / 60, int(tElapsed) % 60, s.c_str());
}

}  // namespace STATS
