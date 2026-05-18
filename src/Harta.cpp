#include "Harta.h"
#include "GeneratorRandom.h"
#include <random>

Harta::~Harta() = default;

Harta::Harta(int dim) : dimensiune(dim) {
    bool hartaBuna = false;
    auto& rng = GeneratorRandom::preiaInstanta().preiaGen();
    std::uniform_int_distribution<int> dist100(0, 99);

    while (!hartaBuna) {
        grila.assign(dimensiune, std::vector<char>(dimensiune, '.'));
        grilaVizibilitate.assign(dimensiune, std::vector<bool>(dimensiune, false));

        for (int i = 0; i < dimensiune; i++) {
            grila[0][i] = '#';
            grila[dimensiune - 1][i] = '#';
            grila[i][0] = '#';
            grila[i][dimensiune - 1] = '#';
        }
        for (int i = 1; i < dimensiune - 1; i++) {
            for (int j = 1; j < dimensiune - 1; j++) {
                if (dist100(rng) < 20) {
                    grila[i][j] = '#';
                }
            }
        }
        grila[1][1] = '.';
        grila[1][2] = '.';
        grila[2][1] = '.';
        grila[dimensiune - 2][dimensiune - 2] = '.';
        grila[dimensiune - 2][dimensiune - 3] = '.';

        hartaBuna = verificaDrumBFS(1, 1, dimensiune - 2, dimensiune - 2);
    }
}

Harta::Harta(const Harta& other) = default;

void Harta::swap(Harta& other) noexcept {
    std::swap(dimensiune, other.dimensiune);
    std::swap(grila, other.grila);
    std::swap(grilaVizibilitate, other.grilaVizibilitate);
}

Harta& Harta::operator=(Harta other) {
    swap(other);
    return *this;
}

bool Harta::verificaDrumBFS(int startX, int startY, int endX, int endY) const {
    std::vector<std::vector<bool>> vizitat(dimensiune, std::vector<bool>(dimensiune, false));
    std::queue<std::pair<int, int>> coadaBFS;

    coadaBFS.emplace(startX, startY);
    vizitat[startX][startY] = true;

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    while (!coadaBFS.empty()) {
        auto [cx, cy] = coadaBFS.front();
        coadaBFS.pop();

        if (cx == endX && cy == endY) return true;

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < dimensiune && ny >= 0 && ny < dimensiune) {
                if (!vizitat[nx][ny] && grila[nx][ny] != '#') {
                    vizitat[nx][ny] = true;
                    coadaBFS.emplace(nx, ny);
                }
            }
        }
    }
    return false;
}

int Harta::preiaDimensiunea() const { return dimensiune; }

bool Harta::esteZid(int x, int y) const {
    if (x < 0 || x >= dimensiune || y < 0 || y >= dimensiune) return true;
    return grila[x][y] == '#';
}

char Harta::preiaCelula(int x, int y) const {
    if (x < 0 || x >= dimensiune || y < 0 || y >= dimensiune) return '#';
    return grila[x][y];
}

void Harta::seteazaEntitate(int x, int y, char c) {
    if (x >= 0 && x < dimensiune && y >= 0 && y < dimensiune) grila[x][y] = c;
}

void Harta::curataEntitate(int x, int y) {
    if (x >= 0 && x < dimensiune && y >= 0 && y < dimensiune) {
        if (grila[x][y] == 'J' || grila[x][y] == 'V' || grila[x][y] == 'C'
            || grila[x][y] == 'F' || grila[x][y] == 'G') grila[x][y] = '.';
    }
}

void Harta::calculeazaCampVizual(int centruX, int centruY, int raza) {
    grilaVizibilitate.assign(dimensiune, std::vector<bool>(dimensiune, false));

    for (int i = 0; i < dimensiune; i++) {
        for (int j = 0; j < dimensiune; j++) {
            if (std::pow(i - centruX, 2) + std::pow(j - centruY, 2) <= std::pow(raza, 2)) {
                grilaVizibilitate[i][j] = true;
            }
        }
    }
}

const std::vector<std::vector<char>>& Harta::preiaGrila() const { return grila; }

std::ostream& operator<<(std::ostream& os, const Harta& h) {
    os << "\n   == RADAR: TEREN ==\n";
    for (int i = 0; i < h.dimensiune; i++) {
        for (int j = 0; j < h.dimensiune; j++) {
            if (h.grilaVizibilitate[i][j]) {
                os << h.grila[i][j] << " ";
            } else {
                os << "? ";
            }
        }
        os << "\n";
    }
    return os;
}
