#ifndef HARTA_H
#define HARTA_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>

class Harta {
private:
    std::vector<std::vector<char>> grila;
    std::vector<std::vector<bool>> grilaVizibilitate;
    int dimensiune;

    bool verificaDrumBFS(int startX, int startY, int endX, int endY) const;

public:
    ~Harta();

    explicit Harta(int dim = 15);

    Harta(const Harta& other);
    Harta& operator=(Harta other);

    void swap(Harta& other) noexcept;

    int preiaDimensiunea() const;
    bool esteZid(int x, int y) const;
    char preiaCelula(int x, int y) const;
    void seteazaEntitate(int x, int y, char c);
    void curataEntitate(int x, int y);
    void calculeazaCampVizual(int centruX, int centruY, int raza);

    friend std::ostream& operator<<(std::ostream& os, const Harta& h);
};

#endif
