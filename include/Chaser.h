#ifndef CHASER_H
#define CHASER_H

#include "VanatorAI.h"
#include <memory>

// Inamic care urmărește activ jucătorul (chase)
class Chaser : public VanatorAI {
public:
    explicit Chaser(int startX = 5, int startY = 5);

    void muta(const Jucator& jucator, const Harta& harta) override;
    char preiaSimbol() const override;
    std::string strategieVanatoare() const override;
    std::unique_ptr<VanatorAI> clone() const override;
};

#endif // CHASER_H
