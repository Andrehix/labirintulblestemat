#ifndef LOGGER_JOC_H
#define LOGGER_JOC_H

#include "ObserverJoc.h"
#include "ManagementResurse.h"
#include <iostream>
#include <string>

class LoggerJoc : public ObserverJoc {
private:
    ManagementResurse<std::string> istoric;

public:
    void notifica(const std::string& eveniment) override {
        istoric.adauga(eveniment);
        std::cout << "[LOG] " << eveniment << "\n";
    }

    size_t numarEvenimente() const { return istoric.dimensiune(); }
};

#endif
