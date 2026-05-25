#include "Gardian.h"
#include "GeneratorRandom.h"
#include <random>

Gardian::Gardian(int startX, int startY, int raza)
    : VanatorAI(startX, startY), razaDetectie(raza) {}

void Gardian::muta(const Jucator& jucator, const Harta& harta) {
    int dist = distantaManhattan(preiaXProtected(), preiaYProtected(),
                                  jucator.preiaX(), jucator.preiaY());

    if (dist <= razaDetectie) {
        VanatorAI::muta(jucator, harta);
    } else {
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};

        auto& rng = GeneratorRandom::preiaInstanta().preiaGen();
        std::uniform_int_distribution<int> distDir(0, 3);

        int incercari = 0;
        while (incercari < 4) {
            int dir = distDir(rng);
            int nx = preiaXProtected() + dx[dir];
            int ny = preiaYProtected() + dy[dir];
            if (!harta.esteZid(nx, ny)) {
                seteazaXProtected(nx);
                seteazaYProtected(ny);
                break;
            }
            incercari++;
        }
    }
}

char Gardian::preiaSimbol() const { return 'G'; }

std::string Gardian::strategieVanatoare() const {
    return "Patrulare + Urmarire in raza " + std::to_string(razaDetectie) + " (Gardian)";
}

std::unique_ptr<VanatorAI> Gardian::clone() const {
    return std::make_unique<Gardian>(preiaXProtected(), preiaYProtected(), razaDetectie);
}

void Gardian::alerteazaZona() {
    std::cout << "[GARDIAN] Alarma! Intrus depistat!\n";
}

void Gardian::actiuneSpeciala(const Jucator& jucator) {
    if (std::abs(preiaXProtected() - jucator.preiaX()) <= 2 && std::abs(preiaYProtected() - jucator.preiaY()) <= 2) {
        alerteazaZona();
    }
}

bool Gardian::operator==(const VanatorAI& other) const {
    const auto* g = dynamic_cast<const Gardian*>(&other);
    if (!g) return false;
    return VanatorAI::operator==(other) && razaDetectie == g->razaDetectie;
}

std::string Gardian::mesajInfrangere() const {
    return "Gardianul te-a descoperit in raza lui.";
}
