#ifndef MIMIC_H
#define MIMIC_H

#include "VanatorAI.h"

class Mimic : public VanatorAI {
public:
    Mimic(int x, int y);
    void muta(const Jucator& j, const Harta& h) override;
    std::string strategieVanatoare() const override;
    std::unique_ptr<VanatorAI> clone() const override;
    char preiaSimbol() const override;
    std::string mesajInfrangere() const override;
};

#endif
