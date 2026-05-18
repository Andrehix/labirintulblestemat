#ifndef OBIECT_H
#define OBIECT_H

#include <iostream>
#include <string>

class Obiect {
private:
    std::string nume;
    int bonusEnergie;
    char simbolHarta;

public:
    explicit Obiect(std::string idNume = "Necunoscut", int bonus = 0, char simbol = '?');

    const std::string& preiaNume() const;
    int preiaBonus() const;
    char preiaSimbol() const;

    friend std::ostream& operator<<(std::ostream& os, const Obiect& obj);
};

#endif // OBIECT_H
