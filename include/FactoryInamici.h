#ifndef FACTORY_INAMICI_H
#define FACTORY_INAMICI_H

#include <memory>
#include <string>
#include "VanatorAI.h"
#include "Chaser.h"
#include "Fantoma.h"
#include "Gardian.h"
#include "Exceptii.h"

// Pattern: Factory Method — creează inamici pe baza unui tip (string)
// Asta elimină new-uri împrăștiate prin cod
class FactoryInamici {
public:
    // Factory method — returnează unique_ptr la clasa de bază
    static std::unique_ptr<VanatorAI> creeazaInamic(
        const std::string& tip,
        int x = 5,
        int y = 5,
        int extra = 4  // raza pentru Gardian
    );

    // Funcție șablon (template) — Tema 3: creează un inamic de un tip specific
    template <typename T>
    static std::unique_ptr<VanatorAI> creeazaTip(int x, int y) {
        return std::make_unique<T>(x, y);
    }
};

#endif // FACTORY_INAMICI_H
