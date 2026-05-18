#include "Fantoma.h"
#include "GeneratorRandom.h"
#include <random>

Fantoma::Fantoma(int startX, int startY) : VanatorAI(startX, startY) {}

void Fantoma::muta(const Jucator& jucator, const Harta& harta) {
    (void)jucator;
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    std::vector<std::pair<int, int>> mutariPosibile;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!harta.esteZid(nx, ny)) {
            mutariPosibile.emplace_back(nx, ny);
        }
    }

    if (!mutariPosibile.empty()) {
        auto& rng = GeneratorRandom::preiaInstanta().preiaGen();
        std::uniform_int_distribution<size_t> dist(0, mutariPosibile.size() - 1);
        size_t alegere = dist(rng);
        x = mutariPosibile[alegere].first;
        y = mutariPosibile[alegere].second;
    }
}

char Fantoma::preiaSimbol() const { return 'F'; }

std::string Fantoma::strategieVanatoare() const {
    return "Ratacire haotica (Fantoma)";
}

std::unique_ptr<VanatorAI> Fantoma::clone() const {
    return std::make_unique<Fantoma>(x, y);
}
