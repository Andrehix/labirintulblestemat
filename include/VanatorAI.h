#ifndef VANATOR_AI_H
#define VANATOR_AI_H

#include <iostream>
#include <cstdlib>
#include <memory>
#include "Jucator.h"
#include "Harta.h"

class VanatorAI {
private:
    int x, y;

protected:
    static int distantaManhattan(int x1, int y1, int x2, int y2);

    int preiaXProtected() const { return x; }
    int preiaYProtected() const { return y; }
    void seteazaXProtected(int nouX) { x = nouX; }
    void seteazaYProtected(int nouY) { y = nouY; }

public:
    explicit VanatorAI(int startX = 5, int startY = 5);
    virtual ~VanatorAI() = default;

    int preiaX() const;
    int preiaY() const;

    virtual void muta(const Jucator& jucator, const Harta& harta);
    virtual void actiuneSpeciala(const Jucator&) {}

    virtual std::string strategieVanatoare() const = 0;
    virtual std::string mesajInfrangere() const = 0;

    virtual bool operator==(const VanatorAI& other) const;

    virtual std::unique_ptr<VanatorAI> clone() const = 0;

    void afiseaza(std::ostream& os) const;

    virtual char preiaSimbol() const;

    friend std::ostream& operator<<(std::ostream& os, const VanatorAI& v);
};

#endif
