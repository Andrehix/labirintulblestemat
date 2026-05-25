#ifndef FACTORY_INAMICI_H
#define FACTORY_INAMICI_H

#include <memory>
#include <string>
#include "VanatorAI.h"
#include "Chaser.h"
#include "Fantoma.h"
#include "Gardian.h"
#include "Exceptii.h"

class FactoryInamici {
public:
    static std::unique_ptr<VanatorAI> creeazaInamic(
        const std::string& tip,
        int x = 5,
        int y = 5,
        int extra = 4
    );

    template <typename T>
    static std::unique_ptr<VanatorAI> creeazaTip(int x, int y) {
        return std::make_unique<T>(x, y);
    }
};

#endif
