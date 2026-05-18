#include "VanatorAI.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h>

VanatorAI::VanatorAI(int startX, int startY) : x(startX), y(startY) {}

int VanatorAI::preiaX() const { return x; }
int VanatorAI::preiaY() const { return y; }

void VanatorAI::reseteazaPozitie(int tx, int ty) { x = tx; y = ty; }

int VanatorAI::distantaManhattan(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void VanatorAI::muta(const Jucator& jucator, const Harta& harta) {
    int tintX = jucator.preiaX();
    int tintY = jucator.preiaY();
    int celMaiBunX = x;
    int celMaiBunY = y;
    int minDist = 9999;

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (!harta.esteZid(nx, ny)) {
            int dist = distantaManhattan(nx, ny, tintX, tintY);
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

char VanatorAI::preiaSimbol() const { return 'V'; }

void VanatorAI::afiseaza(std::ostream& os) const {
    os << fmt::format("Inamic '{}' => (X: {}, Y: {}) | Strategie: {}",
                       preiaSimbol(), x, y, strategieVanatoare());
}

std::ostream& operator<<(std::ostream& os, const VanatorAI& v) {
    v.afiseaza(os);
    return os;
}
