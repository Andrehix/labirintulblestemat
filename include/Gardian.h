#ifndef GARDIAN_H
#define GARDIAN_H

#include "VanatorAI.h"
#include <memory>

// Inamic care patrulează și atacă doar când jucătorul e aproape
class Gardian : public VanatorAI {
private:
    int razaDetectie;

public:
    explicit Gardian(int startX = 5, int startY = 5, int raza = 4);

    void muta(const Jucator& jucator, const Harta& harta) override;
    char preiaSimbol() const override;
    std::string strategieVanatoare() const override;
    std::unique_ptr<VanatorAI> clone() const override;
};

#endif // GARDIAN_H
