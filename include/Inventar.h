#ifndef INVENTAR_H
#define INVENTAR_H

#include <iostream>
#include <vector>
#include "Obiect.h"

class Inventar {
private:
    std::vector<Obiect> elemente;
    int capacitateMaxima;

public:
    explicit Inventar(int cap = 5);

    bool adauga(const Obiect& obj);
    void afiseazaInventar() const;
    int consumaPrimulObiect();
    bool contineObiectCuSimbol(char simbol) const;
    void eliminaObiectCuSimbol(char simbol);
    size_t dimensiune() const;
    int capacitate() const;

    friend std::ostream& operator<<(std::ostream& os, const Inventar& inv);
};

#endif // INVENTAR_H
