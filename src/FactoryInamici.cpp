#include "FactoryInamici.h"

std::unique_ptr<VanatorAI> FactoryInamici::creeazaInamic(
    const std::string& tip, int x, int y, int extra) {

    if (tip == "chaser") {
        return std::make_unique<Chaser>(x, y);
    } else if (tip == "fantoma") {
        return std::make_unique<Fantoma>(x, y);
    } else if (tip == "gardian") {
        return std::make_unique<Gardian>(x, y, extra);
    } else {
        throw EroareJucator("Tip de inamic necunoscut: " + tip);
    }
}
