#include "MotorJoc.h"
#include "GeneratorRandom.h"
#include <random>

int MotorJoc::numarTotalJocuri = 0;

MotorJoc::MotorJoc(int dimHarta)
    : harta(dimHarta),
      jucator(1, 1, ConfiguratorJoc::preiaInstanta().preiaSetareInt("energie_initiala", 40)),
      xDestinatie(dimHarta - 2), yDestinatie(dimHarta - 2),
      scor(0), cheiePlasata(false) {

    plaseazaInamici();
    genereazaLoot();
    numarTotalJocuri++;
}

MotorJoc::~MotorJoc() = default;

void MotorJoc::plaseazaInamici() {
    std::ifstream fisierInamici("assets/inamici.txt");
    if (fisierInamici.is_open()) {
        std::string tip;
        int x, y, extra;
        while (fisierInamici >> tip >> x >> y >> extra) {
            if (tip.empty() || tip[0] == '#') continue;
            inamici.push_back(FactoryInamici::creeazaInamic(tip, x, y, extra));
        }
        fisierInamici.close();
        return;
    }

    int numar = ConfiguratorJoc::preiaInstanta().preiaSetareInt("numar_inamici", 3);
    int dim = harta.preiaDimensiunea();

    if (numar >= 1)
        inamici.push_back(FactoryInamici::creeazaInamic("chaser", dim - 3, 3));
    if (numar >= 2)
        inamici.push_back(FactoryInamici::creeazaInamic("fantoma", dim / 2, dim / 2));
    if (numar >= 3)
        inamici.push_back(FactoryInamici::creeazaInamic("gardian", dim - 4, dim - 4, 4));
    if (numar >= 4)
        inamici.push_back(FactoryInamici::creeazaTip<Fantoma>(dim / 3, dim / 3));
}

void MotorJoc::genereazaLoot() {
    auto& rng = GeneratorRandom::preiaInstanta().preiaGen();
    int maxLoot = ConfiguratorJoc::preiaInstanta().preiaSetareInt("numar_loot", 5);
    int dim = harta.preiaDimensiunea();
    std::uniform_int_distribution<int> distDim(0, dim - 1);
    std::uniform_int_distribution<int> distTip(0, 2);
    std::uniform_int_distribution<int> distDauna(5, 12);

    int incercariLoot = 0;
    const int maxIncercariLoot = maxLoot * 100;
    while (static_cast<int>(obiectePeHarta.size()) < maxLoot && incercariLoot < maxIncercariLoot) {
        incercariLoot++;
        int bx = distDim(rng);
        int by = distDim(rng);
        bool ocupat = false;
        for (const auto& coord : coordObiecte) {
            if (coord.first == bx && coord.second == by) {
                ocupat = true; break;
            }
        }
        if (!harta.esteZid(bx, by) && !(bx == 1 && by == 1) && !ocupat) {
            Obiect ob;
            int tip = distTip(rng);
            if (tip == 0)
                ob = Obiect("Baterie Duracell", 18, 'B');
            else if (tip == 1)
                ob = Obiect("Teleportor", 0, 'P');
            else
                ob = Obiect("Elixir Vital", 30, 'E');

            obiectePeHarta.push_back(ob);
            coordObiecte.emplace_back(bx, by);
            harta.seteazaEntitate(bx, by, ob.preiaSimbol());
        }
    }

    if (!cheiePlasata) {
        bool plasat = false;
        int incercariCheie = 0;
        const int maxIncercariCheie = dim * dim * 2;
        while (!plasat && incercariCheie < maxIncercariCheie) {
            incercariCheie++;
            int kx = distDim(rng);
            int ky = distDim(rng);
            if (!harta.esteZid(kx, ky) && !(kx == 1 && ky == 1)
                && !(kx == xDestinatie && ky == yDestinatie)) {
                harta.seteazaEntitate(kx, ky, 'K');
                plasat = true;
                cheiePlasata = true;
            }
        }
    }

    int numarCapcane = ConfiguratorJoc::preiaInstanta().preiaSetareInt("numar_capcane", 4);
    for (int i = 0; i < numarCapcane; i++) {
        int cx = distDim(rng);
        int cy = distDim(rng);
        if (!harta.esteZid(cx, cy) && !(cx == 1 && cy == 1)
            && !(cx == xDestinatie && cy == yDestinatie)) {
            bool suprapus = false;
            for (const auto& cap : pozitiiCapcane) {
                if (cap.first == cx && cap.second == cy) { suprapus = true; break; }
            }
            for (const auto& coord : coordObiecte) {
                if (coord.first == cx && coord.second == cy) { suprapus = true; break; }
            }
            if (!suprapus) {
                pozitiiCapcane.emplace_back(cx, cy);
                dauneCapcane.push_back(distDauna(rng));
                harta.seteazaEntitate(cx, cy, 'T');
            }
        }
    }
}

void MotorJoc::ruleazaJoc() {
    auto& rng = GeneratorRandom::preiaInstanta().preiaGen();
    std::uniform_int_distribution<int> dist100(0, 99);
    std::uniform_int_distribution<int> distDim(0, harta.preiaDimensiunea() - 1);

    std::cout << "\n============================================\n";
    std::cout << "  BUN VENIT IN LABIRINTUL BLESTEMAT (V3.0)  \n";
    std::cout << "============================================\n";
    std::cout << "Legenda: J=Tu, C=Chaser, F=Fantoma, G=Gardian,\n";
    std::cout << "         B=Baterie, P=Teleportor, E=Elixir, K=Cheie,\n";
    std::cout << "         T=Capcana, D=Iesire, ?=Ceata\n\n";

    int razaViz = ConfiguratorJoc::preiaInstanta().preiaSetareInt("raza_vizibilitate", 3);

    while (true) {
        int prevJX = jucator.preiaX();
        int prevJY = jucator.preiaY();
        std::vector<std::pair<int, int>> prevInamici;
        prevInamici.reserve(inamici.size());
        for (const auto& inamic : inamici) {
            prevInamici.emplace_back(inamic->preiaX(), inamic->preiaY());
        }

        harta.seteazaEntitate(xDestinatie, yDestinatie, 'D');

        for (size_t i = 0; i < coordObiecte.size(); i++) {
            if (coordObiecte[i].first != -1) {
                harta.seteazaEntitate(coordObiecte[i].first, coordObiecte[i].second,
                                      obiectePeHarta[i].preiaSimbol());
            }
        }

        for (const auto& cap : pozitiiCapcane) {
            harta.seteazaEntitate(cap.first, cap.second, 'T');
        }

        for (size_t i = 0; i < coordObiecte.size(); i++) {
            if (coordObiecte[i].first == jucator.preiaX() &&
                coordObiecte[i].second == jucator.preiaY()) {
                if (jucator.adunaObiect(obiectePeHarta[i])) {
                    std::cout << "\n[!] Ai gasit: " << obiectePeHarta[i].preiaNume() << "\n";
                    scor += 10;
                    coordObiecte[i] = {-1, -1};
                }
            }
        }

        if (harta.preiaCelula(jucator.preiaX(), jucator.preiaY()) == 'K') {
            jucator.adunaObiect(Obiect("Cheie", 0, 'K'));
            harta.seteazaEntitate(jucator.preiaX(), jucator.preiaY(), '.');
            scor += 25;
        }

        for (size_t i = 0; i < pozitiiCapcane.size(); i++) {
            if (pozitiiCapcane[i].first == jucator.preiaX() &&
                pozitiiCapcane[i].second == jucator.preiaY()) {
                int dauna = dauneCapcane[i];
                std::cout << "\n[!!!] Ai calcat intr-o capcana! Pierzi " << dauna << " energie.\n";
                jucator.scadeEnergie(dauna);
                scor -= 5;
                pozitiiCapcane.erase(pozitiiCapcane.begin() + static_cast<long>(i));
                dauneCapcane.erase(dauneCapcane.begin() + static_cast<long>(i));
                i--;
            }
        }

        harta.seteazaEntitate(jucator.preiaX(), jucator.preiaY(), 'J');
        for (const auto& inamic : inamici) {
            harta.seteazaEntitate(inamic->preiaX(), inamic->preiaY(),
                                  inamic->preiaSimbol());
        }

        harta.calculeazaCampVizual(jucator.preiaX(), jucator.preiaY(), razaViz);

        std::cout << *this;
        std::cout << "\nScor curent: " << scor << "\n";
        std::cout << "Actiuni: [w/a/s/d]=Misca | [e]=Foloseste Baterie | [t]=Teleportor | [q]=Abandon\n";
        std::cout << "Alege miscare: ";

        bool capturat = false;
        for (const auto& inamic : inamici) {
            if (jucator.preiaX() == inamic->preiaX() &&
                jucator.preiaY() == inamic->preiaY()) {
                capturat = true;
                break;
            }
        }

        if (capturat) {
            std::cout << "\n>>> INFRANGERE! Un spectru ti-a furat sufletul! Game Over. <<<\n";
            break;
        }
        if (jucator.preiaX() == xDestinatie && jucator.preiaY() == yDestinatie) {
            if (jucator.posedaCheie()) {
                std::cout << "\n>>> SUCCES! Ai scapat din labirint! <<<\n";
                scor += 50 + jucator.preiaEnergie() / 2;
                std::cout << "Scor final: " << scor << "\n";
                break;
            } else {
                std::cout << "\n[!] Iesirea este incuiata. Ai nevoie de cheie.\n";
            }
        }
        if (jucator.preiaEnergie() <= 0) {
            std::cout << "\n>>> INFRANGERE! Lanterna s-a stins definitiv. <<<\n";
            break;
        }

        char optiune;
        if (!(std::cin >> optiune) || optiune == 'q') {
            std::cout << "\nAi abandonat cautarea. Scor final: " << scor << "\n";
            break;
        }

        if (optiune == 'e') {
            jucator.beaPotiuneDinInventar();
        } else if (optiune == 't') {
            if (jucator.folosesteTeleportor()) {
                int nx = 0, ny = 0;
                do {
                    nx = distDim(rng);
                    ny = distDim(rng);
                } while (harta.esteZid(nx, ny));
                jucator.seteazaPozitia(nx, ny);
                std::cout << "Te-ai teleportat la (" << nx << ", " << ny << ").\n";
            }
        } else if (optiune == 'w' || optiune == 'a' || optiune == 's' || optiune == 'd') {
            jucator.muta(optiune, harta);
        } else {
            std::cout << "\nComanda invalida.";
        }

        for (const auto& inamic : inamici) {
            if (dist100(rng) > 20) {
                inamic->muta(jucator, harta);
            }
        }

        harta.curataEntitate(prevJX, prevJY);
        for (const auto& prev : prevInamici) {
            harta.curataEntitate(prev.first, prev.second);
        }
    }
}

int MotorJoc::preiaNumarTotalJocuri() {
    return numarTotalJocuri;
}

std::ostream& operator<<(std::ostream& os, const MotorJoc& mj) {
    os << mj.jucator << "\n";
    for (const auto& inamic : mj.inamici) {
        os << *inamic << "\n";
    }
    os << mj.harta;
    return os;
}
