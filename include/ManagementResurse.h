#ifndef MANAGEMENT_RESURSE_H
#define MANAGEMENT_RESURSE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "Exceptii.h"

// Clasă șablon (Template class) — Tema 3
// Gestionează o colecție de elemente de orice tip (Obiect, inamici, etc.)
// Oferă statistici, sortare, filtrare, salvare/încărcare
template <typename T>
class ManagementResurse {
private:
    std::vector<T> resurse;

public:
    ManagementResurse() = default;

    ManagementResurse(const ManagementResurse&) = default;
    ManagementResurse& operator=(const ManagementResurse&) = default;
    ~ManagementResurse() = default;

    void adauga(const T& element) {
        resurse.push_back(element);
    }

    void adaugaMultiple(const std::vector<T>& elemente) {
        for (const auto& el : elemente) {
            resurse.push_back(el);
        }
    }

    void sterge(size_t index) {
        if (index >= resurse.size()) {
            throw EroareInventar("Index depasit in ManagementResurse::sterge");
        }
        resurse.erase(resurse.begin() + static_cast<long>(index));
    }

    const T& preia(size_t index) const {
        if (index >= resurse.size()) {
            throw EroareInventar("Index depasit in ManagementResurse::preia");
        }
        return resurse[index];
    }

    T& preia(size_t index) {
        if (index >= resurse.size()) {
            throw EroareInventar("Index depasit in ManagementResurse::preia");
        }
        return resurse[index];
    }

    size_t dimensiune() const { return resurse.size(); }
    bool gol() const { return resurse.empty(); }

    const std::vector<T>& preiaToate() const { return resurse; }

    // Sortare cu comparator
    template <typename Comparator>
    void sorteaza(Comparator comp) {
        std::sort(resurse.begin(), resurse.end(), comp);
    }

    // Filtrare: returnează elementele care satisfac predicatul
    template <typename Predicat>
    std::vector<T> filtreaza(Predicat pred) const {
        std::vector<T> rezultat;
        for (const auto& el : resurse) {
            if (pred(el)) {
                rezultat.push_back(el);
            }
        }
        return rezultat;
    }

    // Golește colecția
    void goleste() { resurse.clear(); }

    friend std::ostream& operator<<(std::ostream& os, const ManagementResurse<T>& mr) {
        os << "ManagementResurse: " << mr.resurse.size() << " elemente\n";
        for (size_t i = 0; i < mr.resurse.size(); ++i) {
            os << "  [" << i << "] " << mr.resurse[i] << "\n";
        }
        return os;
    }
};

// Funcție șablon (Template function) — Tema 3
// Găsește elementul maxim dintr-un vector pe baza unui comparator
template <typename T, typename Comparator>
T gasesteMaxim(const std::vector<T>& colectie, Comparator comp) {
    if (colectie.empty()) {
        throw std::runtime_error("Colectie vida in gasesteMaxim");
    }
    T maxim = colectie[0];
    for (size_t i = 1; i < colectie.size(); ++i) {
        if (comp(colectie[i], maxim)) {
            maxim = colectie[i];
        }
    }
    return maxim;
}

#endif // MANAGEMENT_RESURSE_H
