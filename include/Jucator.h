#ifndef JUCATOR_H
#define JUCATOR_H

#include <iostream>
#include "Inventar.h"
#include "Obiect.h"
#include "Harta.h"

class Jucator {
private:
    int x, y;
    int energie;
    Inventar rucsac;
    bool areCheie;

public:
    explicit Jucator(int startX = 1, int startY = 1, int startEnergie = 60);

    int preiaX() const;
    int preiaY() const;
    int preiaEnergie() const;
    bool posedaCheie() const;

    void incarcaEnergie(int prada);
    void scadeEnergie(int val);
    bool adunaObiect(const Obiect& obj);
    void beaPotiuneDinInventar();
    bool folosesteTeleportor();
    void seteazaPozitia(int nx, int ny);
    void afiseazaStatusInventar() const;
    void muta(char directie, const Harta& harta);

    friend std::ostream& operator<<(std::ostream& os, const Jucator& j);
};

#endif // JUCATOR_H
