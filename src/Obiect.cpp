#include "Obiect.h"
#include <utility>

Obiect::Obiect(std::string idNume, int bonus, char simbol)
    : nume(std::move(idNume)), bonusEnergie(bonus), simbolHarta(simbol) {}

const std::string& Obiect::preiaNume() const { return nume; }
int Obiect::preiaBonus() const { return bonusEnergie; }
char Obiect::preiaSimbol() const { return simbolHarta; }

std::ostream& operator<<(std::ostream& os, const Obiect& obj) {
    os << "[" << obj.nume << " | Bonus: " << obj.bonusEnergie << ", Simbol: " << obj.simbolHarta << "]";
    return os;
}
