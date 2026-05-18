#ifndef GENERATOR_RANDOM_H
#define GENERATOR_RANDOM_H

#include <random>

class GeneratorRandom {
private:
    std::mt19937 gen;
    GeneratorRandom() : gen(std::random_device{}()) {}

public:
    GeneratorRandom(const GeneratorRandom&) = delete;
    GeneratorRandom& operator=(const GeneratorRandom&) = delete;

    static GeneratorRandom& preiaInstanta() {
        static GeneratorRandom instanta;
        return instanta;
    }

    std::mt19937& preiaGen() { return gen; }
};

#endif
