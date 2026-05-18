#include "Exceptii.h"

EroareJoc::EroareJoc(const std::string& mesaj)
    : std::runtime_error("EroareJoc: " + mesaj) {}

EroareHarta::EroareHarta(const std::string& mesaj)
    : EroareJoc("EroareHarta: " + mesaj) {}

EroareJucator::EroareJucator(const std::string& mesaj)
    : EroareJoc("EroareJucator: " + mesaj) {}

EroareInventar::EroareInventar(const std::string& mesaj)
    : EroareJoc("EroareInventar: " + mesaj) {}
