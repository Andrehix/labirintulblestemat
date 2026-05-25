#ifndef CONFIGURATOR_JOC_H
#define CONFIGURATOR_JOC_H

#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include "Exceptii.h"

class ConfiguratorJoc {
private:
    std::map<std::string, std::string> setari;

    ConfiguratorJoc();

public:
    ConfiguratorJoc(const ConfiguratorJoc&) = delete;
    ConfiguratorJoc& operator=(const ConfiguratorJoc&) = delete;

    ~ConfiguratorJoc();

    static ConfiguratorJoc& preiaInstanta();

    void incarcaDinFisier(const std::string& caleFisier);

    int preiaSetareInt(const std::string& cheie, int implicit = 0) const;

    void afiseazaSetari() const;

    friend std::ostream& operator<<(std::ostream& os, const ConfiguratorJoc& cfg);
};

#endif
