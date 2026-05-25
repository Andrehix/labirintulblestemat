#include "Exceptii.h"

EroareJoc::EroareJoc(const std::string& mesaj)
    : std::runtime_error("EroareJoc: " + mesaj) {}

EroareInitializare::EroareInitializare(const std::string& mesaj)
    : EroareJoc("EroareInitializare: " + mesaj) {}

EroareFisierLipsa::EroareFisierLipsa(const std::string& mesaj)
    : EroareInitializare("Fisier Lipsa: " + mesaj) {}

EroareFormatFisier::EroareFormatFisier(const std::string& mesaj)
    : EroareInitializare("Format Fisier: " + mesaj) {}

EroareLogica::EroareLogica(const std::string& mesaj)
    : EroareJoc("EroareLogica: " + mesaj) {}

EroareActiuneInvalida::EroareActiuneInvalida(const std::string& mesaj)
    : EroareLogica("Actiune Invalida: " + mesaj) {}
