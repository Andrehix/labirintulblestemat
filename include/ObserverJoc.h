#ifndef OBSERVER_JOC_H
#define OBSERVER_JOC_H

#include <string>

class ObserverJoc {
public:
    virtual ~ObserverJoc() = default;
    virtual void notifica(const std::string& eveniment) = 0;
};

#endif
