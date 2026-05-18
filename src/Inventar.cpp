#include "Inventar.h"
#include <algorithm>

Inventar::Inventar(int cap) : capacitateMaxima(cap) {}

bool Inventar::adauga(const Obiect& obj) {
    if (static_cast<int>(elemente.size()) < capacitateMaxima) {
        elemente.push_back(obj);
        return true;
    }
    return false;
}

void Inventar::afiseazaInventar() const {
    if (elemente.empty()) {
        std::cout << "Inventarul este gol.\n";
        return;
    }
    std::cout << "Inventar (" << elemente.size() << "/" << capacitateMaxima << "):\n";
    for (size_t i = 0; i < elemente.size(); i++) {
        std::cout << "  " << i + 1 << ". " << elemente[i] << "\n";
    }
}

int Inventar::consumaPrimulObiect() {
    if (elemente.empty()) return 0;
    int bonus = elemente[0].preiaBonus();
    elemente.erase(elemente.begin());
    return bonus;
}

bool Inventar::contineObiectCuSimbol(char simbol) const {
    return std::any_of(elemente.begin(), elemente.end(),
        [simbol](const Obiect& ob) { return ob.preiaSimbol() == simbol; });
}

void Inventar::eliminaObiectCuSimbol(char simbol) {
    for (auto it = elemente.begin(); it != elemente.end(); ++it) {
        if (it->preiaSimbol() == simbol) {
            elemente.erase(it);
            return;
        }
    }
}

size_t Inventar::dimensiune() const { return elemente.size(); }
int Inventar::capacitate() const { return capacitateMaxima; }

std::ostream& operator<<(std::ostream& os, const Inventar& inv) {
    os << "Inventar capacitate: " << inv.capacitateMaxima << ", iteme curent: " << inv.elemente.size();
    return os;
}
