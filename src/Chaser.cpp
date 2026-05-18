#include "Chaser.h"
#include <algorithm>
#include <climits>

Chaser::Chaser(int startX, int startY) : VanatorAI(startX, startY) {}

void Chaser::muta(const Jucator& jucator, const Harta& harta) {
    int tintX = jucator.preiaX();
    int tintY = jucator.preiaY();

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    int celMaiBunX = x;
    int celMaiBunY = y;
    int minDist = INT_MAX;

    int diffX = std::abs(tintX - x);
    int diffY = std::abs(tintY - y);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (!harta.esteZid(nx, ny)) {
            int dist = distantaManhattan(nx, ny, tintX, tintY);
            if (diffX > diffY && (dx[i] != 0)) dist -= 1;
            if (diffY > diffX && (dy[i] != 0)) dist -= 1;

            if (dist < minDist) {
                minDist = dist;
                celMaiBunX = nx;
                celMaiBunY = ny;
            }
        }
    }

    x = celMaiBunX;
    y = celMaiBunY;
}

char Chaser::preiaSimbol() const { return 'C'; }

std::string Chaser::strategieVanatoare() const {
    return "Urmarire directa (Chaser)";
}

std::unique_ptr<VanatorAI> Chaser::clone() const {
    return std::make_unique<Chaser>(x, y);
}
