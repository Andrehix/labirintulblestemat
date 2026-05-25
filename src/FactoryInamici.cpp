#include "Mimic.h"
#include "FactoryInamici.h"

std::unique_ptr<VanatorAI> FactoryInamici::creeazaInamic(
    const std::string& tip, int x, int y, int extra) {

    if (tip == "chaser") {
        return creeazaTip<Chaser>(x, y);
    } else if (tip == "fantoma") {
        return creeazaTip<Fantoma>(x, y);
    } else if (tip == "mimic") {
        return creeazaTip<Mimic>(x, y);
    } else if (tip == "gardian") {
        return std::make_unique<Gardian>(x, y, extra);
    } else {
        throw EroareActiuneInvalida("Tip de inamic necunoscut: " + tip);
    }
}
