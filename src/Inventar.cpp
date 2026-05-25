#include "Inventar.h"
#include <algorithm>

Inventar::Inventar(int cap) : capacitateMaxima(cap) {}

bool Inventar::adauga(const Obiect& obj) {
    if (static_cast<int>(elemente.dimensiune()) < capacitateMaxima) {
        elemente.adauga(obj);
        return true;
    }
    return false;
}

void Inventar::afiseazaInventar() const {
    if (elemente.gol()) {
        std::cout << "Inventarul este gol.\n";
        return;
    }
    std::cout << "Inventar (" << elemente.dimensiune() << "/" << capacitateMaxima << "):\n";
    for (size_t i = 0; i < elemente.dimensiune(); i++) {
        std::cout << "  " << i + 1 << ". " << elemente.preia(i) << "\n";
    }
}

int Inventar::consumaPrimulObiect() {
    if (elemente.gol()) return 0;
    int bonus = elemente.preia(0).preiaBonus();
    elemente.sterge(0);
    return bonus;
}

bool Inventar::contineObiectCuSimbol(char simbol) const {
    const auto& vec = elemente.preiaToate();
    return std::any_of(vec.begin(), vec.end(),
        [simbol](const Obiect& ob) { return ob.preiaSimbol() == simbol; });
}

void Inventar::eliminaObiectCuSimbol(char simbol) {
    const auto& vec = elemente.preiaToate();
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i].preiaSimbol() == simbol) {
            elemente.sterge(i);
            return;
        }
    }
}

size_t Inventar::dimensiune() const { return elemente.dimensiune(); }

std::ostream& operator<<(std::ostream& os, const Inventar& inv) {
    os << "Inventar capacitate: " << inv.capacitateMaxima << ", iteme curent: " << inv.elemente.dimensiune();
    os << "\n";
    for (size_t i = 0; i < inv.elemente.dimensiune(); ++i) {
        os << "  [" << i << "] " << inv.elemente.preia(i) << "\n";
    }
    return os;
}
