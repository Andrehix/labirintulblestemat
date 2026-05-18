#include "Gardian.h"
#include "GeneratorRandom.h"
#include <random>

Gardian::Gardian(int startX, int startY, int raza)
    : VanatorAI(startX, startY), razaDetectie(raza) {}

void Gardian::muta(const Jucator& jucator, const Harta& harta) {
    int dist = distantaManhattan(x, y, jucator.preiaX(), jucator.preiaY());

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
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (!harta.esteZid(nx, ny)) {
                x = nx;
                y = ny;
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
    return std::make_unique<Gardian>(x, y, razaDetectie);
}
