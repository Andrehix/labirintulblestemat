#ifndef MANAGEMENT_RESURSE_H
#define MANAGEMENT_RESURSE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "Exceptii.h"

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

    void sterge(size_t index) {
        if (index >= resurse.size()) {
            throw EroareActiuneInvalida("Index depasit in ManagementResurse::sterge");
        }
        resurse.erase(resurse.begin() + static_cast<long>(index));
    }

    const T& preia(size_t index) const {
        if (index >= resurse.size()) {
            throw EroareActiuneInvalida("Index depasit in ManagementResurse::preia");
        }
        return resurse[index];
    }

    T& preia(size_t index) {
        if (index >= resurse.size()) {
            throw EroareActiuneInvalida("Index depasit in ManagementResurse::preia");
        }
        return resurse[index];
    }

    size_t dimensiune() const { return resurse.size(); }
    bool gol() const { return resurse.empty(); }

    const std::vector<T>& preiaToate() const { return resurse; }

    template <typename Comparator>
    void sorteaza(Comparator comp) {
        std::sort(resurse.begin(), resurse.end(), comp);
    }

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

    friend std::ostream& operator<<(std::ostream& os, const ManagementResurse<T>& mr) {
        os << "ManagementResurse: " << mr.resurse.size() << " elemente\n";
        for (size_t i = 0; i < mr.resurse.size(); ++i) {
            os << "  [" << i << "] " << mr.resurse[i] << "\n";
        }
        return os;
    }
};

#endif
