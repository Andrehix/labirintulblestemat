#include "Jucator.h"

Jucator::Jucator(int startX, int startY, int startEnergie)
    : x(startX), y(startY), energie(startEnergie), rucsac(3), areCheie(false) {}

int Jucator::preiaX() const { return x; }
int Jucator::preiaY() const { return y; }
int Jucator::preiaEnergie() const { return energie; }
bool Jucator::posedaCheie() const { return areCheie; }

void Jucator::incarcaEnergie(int prada) { energie += prada; }

void Jucator::scadeEnergie(int val) {
    energie -= val;
    if (energie < 0) energie = 0;
}

bool Jucator::adunaObiect(const Obiect& obj) {
    if (obj.preiaSimbol() == 'K') {
        areCheie = true;
        std::cout << "\n[!] Ai gasit cheia. Acum poti iesi din labirint.\n";
        return true;
    }
    return rucsac.adauga(obj);
}

void Jucator::beaPotiuneDinInventar() {
    int val = rucsac.consumaPrimulObiect();
    if (val > 0) {
        std::cout << "\n[!] Ai aplicat un obiect si ai castigat " << val << " baterie!\n";
        energie += val;
    } else {
        std::cout << "\n[!] Nimic in inventar.\n";
    }
}

bool Jucator::folosesteTeleportor() {
    if (rucsac.contineObiectCuSimbol('P')) {
        rucsac.eliminaObiectCuSimbol('P');
        std::cout << "\n[!] Teleportare activata! Esti proiectat aleatoriu pe harta.\n";
        return true;
    }
    std::cout << "\n[!] Nu ai niciun teleportor in inventar.\n";
    return false;
}

void Jucator::seteazaPozitia(int nx, int ny) { x = nx; y = ny; }

void Jucator::afiseazaStatusInventar() const { rucsac.afiseazaInventar(); }

void Jucator::muta(char directie, const Harta& harta) {
    int nouX = x, nouY = y;

    if (directie == 'w') nouX--;
    else if (directie == 's') nouX++;
    else if (directie == 'a') nouY--;
    else if (directie == 'd') nouY++;

    if (!harta.esteZid(nouX, nouY) && energie > 0) {
        x = nouX;
        y = nouY;
        energie--;
    } else if (harta.esteZid(nouX, nouY)) {
        std::cout << "\n[Lovire] BAM! Te-ai izbit cu capul de un pietroi antic. Mai multa grija!\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Jucator& j) {
    os << "---------------------------------\n";
    os << "EXPLORATOR 'J' => (X: " << j.x << ", Y: " << j.y << ") | Baterie Lanterna: " << j.energie << "%\n";
    os << "Cheie: " << (j.areCheie ? "Da" : "Nu") << "\n";
    os << j.rucsac;
    return os;
}
