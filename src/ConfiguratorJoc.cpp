#include "ConfiguratorJoc.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <json.hpp>

using json = nlohmann::json;

ConfiguratorJoc::ConfiguratorJoc() {
    setari["dimensiune_harta"] = "14";
    setari["energie_initiala"] = "40";
    setari["numar_inamici"] = "3";
    setari["capacitate_inventar"] = "3";
    setari["raza_vizibilitate"] = "3";
    setari["numar_capcane"] = "4";
    setari["numar_loot"] = "5";
}

ConfiguratorJoc::~ConfiguratorJoc() = default;

ConfiguratorJoc& ConfiguratorJoc::preiaInstanta() {
    static ConfiguratorJoc instanta;
    return instanta;
}

void ConfiguratorJoc::incarcaDinFisier(const std::string& caleFisier) {
    std::ifstream fisier(caleFisier);
    if (!fisier.is_open()) {
        throw EroareFisierLipsa("Nu s-a putut deschide fisierul de configurare: " + caleFisier);
    }

    std::string linie;
    int numarLinie = 0;
    while (std::getline(fisier, linie)) {
        numarLinie++;
        if (linie.empty() || linie[0] == '#') continue;

        auto poz = linie.find('=');
        if (poz == std::string::npos) {
            throw EroareFormatFisier("Format invalid in fisierul de configurare la linia "
                                 + std::to_string(numarLinie) + ": " + linie);
        }

        std::string cheie = linie.substr(0, poz);
        std::string valoare = linie.substr(poz + 1);
        cheie.erase(0, cheie.find_first_not_of(" \t"));
        cheie.erase(cheie.find_last_not_of(" \t") + 1);
        valoare.erase(0, valoare.find_first_not_of(" \t"));
        valoare.erase(valoare.find_last_not_of(" \t") + 1);
        setari[cheie] = valoare;
    }
    fisier.close();
}

int ConfiguratorJoc::preiaSetareInt(const std::string& cheie, int implicit) const {
    auto it = setari.find(cheie);
    if (it != setari.end()) {
        try {
            return std::stoi(it->second);
        } catch (...) {
            return implicit;
        }
    }
    return implicit;
}

void ConfiguratorJoc::afiseazaSetari() const {
    std::cout << "=== Configuratii Joc ===\n";
    for (const auto& [cheie, val] : setari) {
        std::cout << "  " << cheie << " = " << val << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const ConfiguratorJoc& cfg) {
    os << "ConfiguratorJoc: " << cfg.setari.size() << " setari";
    return os;
}
