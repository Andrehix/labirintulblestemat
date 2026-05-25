#ifndef GARDIAN_H
#define GARDIAN_H

#include "VanatorAI.h"
#include <memory>

class Gardian : public VanatorAI {
private:
    int razaDetectie;

public:
    static void alerteazaZona();

    explicit Gardian(int startX = 5, int startY = 5, int raza = 4);

    void muta(const Jucator& jucator, const Harta& harta) override;
    void actiuneSpeciala(const Jucator& jucator) override;
    bool operator==(const VanatorAI& other) const override;
    char preiaSimbol() const override;
    std::string strategieVanatoare() const override;
    std::unique_ptr<VanatorAI> clone() const override;
    std::string mesajInfrangere() const override;
};

#endif
