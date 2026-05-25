#include "Mimic.h"
#include <iostream>

Mimic::Mimic(int x, int y) : VanatorAI(x, y) {}

void Mimic::muta(const Jucator& /*j*/, const Harta& /*h*/) {
}

std::string Mimic::strategieVanatoare() const {
    return "Deghizare in obiect lootabil";
}

char Mimic::preiaSimbol() const {
    return 'L';
}

std::unique_ptr<VanatorAI> Mimic::clone() const {
    return std::make_unique<Mimic>(preiaXProtected(), preiaYProtected());
}

std::string Mimic::mesajInfrangere() const {
    return "Un Mimic te-a devorat cand ai vrut sa il iei!";
}
