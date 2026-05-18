#ifndef MOTOR_JOC_H
#define MOTOR_JOC_H

#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Harta.h"
#include "Jucator.h"
#include "VanatorAI.h"
#include "Obiect.h"
#include "ConfiguratorJoc.h"
#include "FactoryInamici.h"
#include "Exceptii.h"

class MotorJoc {
private:
    Harta harta;
    Jucator jucator;
    std::vector<std::unique_ptr<VanatorAI>> inamici;
    int xDestinatie, yDestinatie;

    std::vector<Obiect> obiectePeHarta;
    std::vector<std::pair<int, int>> coordObiecte;
    std::vector<std::pair<int, int>> pozitiiCapcane;
    std::vector<int> dauneCapcane;

    int scor;
    bool cheiePlasata;

    // Static counter — câte jocuri s-au creat
    static int numarTotalJocuri;

    void genereazaLoot();
    void plaseazaInamici();

public:
    explicit MotorJoc(int dimHarta = 14);
    ~MotorJoc();

    MotorJoc(const MotorJoc&) = delete;
    MotorJoc& operator=(const MotorJoc&) = delete;

    void ruleazaJoc();
    static int preiaNumarTotalJocuri();

    friend std::ostream& operator<<(std::ostream& os, const MotorJoc& mj);
};

#endif // MOTOR_JOC_H
