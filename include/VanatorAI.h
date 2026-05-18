#ifndef VANATOR_AI_H
#define VANATOR_AI_H

#include <iostream>
#include <cstdlib>
#include <memory>
#include "Jucator.h"
#include "Harta.h"

class VanatorAI {
protected:
    int x, y;

    static int distantaManhattan(int x1, int y1, int x2, int y2);

public:
    explicit VanatorAI(int startX = 5, int startY = 5);
    virtual ~VanatorAI() = default;

    int preiaX() const;
    int preiaY() const;
    void reseteazaPozitie(int tx, int ty);

    // ── funcții virtuale (Tema 2) ──
    virtual void muta(const Jucator& jucator, const Harta& harta);

    // Funcție virtuală specifică temei: strategia de vânătoare (nu simplu getter/setter)
    virtual std::string strategieVanatoare() const = 0;

    // Constructor virtual (clone)
    virtual std::unique_ptr<VanatorAI> clone() const = 0;

    // Interfață non-virtuală: afișare care apelează funcția virtuală privată
    void afiseaza(std::ostream& os) const;

    // Simbolul trebuie să fie virtual pentru polimorfism
    virtual char preiaSimbol() const;

    friend std::ostream& operator<<(std::ostream& os, const VanatorAI& v);
};

#endif // VANATOR_AI_H
