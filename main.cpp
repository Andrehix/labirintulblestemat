#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "include/Obiect.h"
#include "include/Inventar.h"
#include "include/Harta.h"
#include "include/Jucator.h"
#include "include/VanatorAI.h"
#include "include/Fantoma.h"
#include "include/Chaser.h"
#include "include/Gardian.h"
#include "include/MotorJoc.h"
#include "include/ConfiguratorJoc.h"
#include "include/FactoryInamici.h"
#include "include/ManagementResurse.h"
#include "include/Exceptii.h"
#include "include/Example.h"
#include <random>
#include "include/GeneratorRandom.h"
#include <json.hpp>

int main() {
    GeneratorRandom::preiaInstanta();

    Example ex;
    ex.g();

    std::cout << "\n===== CONFIGURARE JOC (Singleton) =====\n";
    try {
        ConfiguratorJoc& cfg = ConfiguratorJoc::preiaInstanta();
        cfg.incarcaDinFisier("assets/config_joc.txt");
        cfg.afiseazaSetari();
        std::cout << cfg << "\n";
        std::cout << "Setare 'dimensiune_harta': " << cfg.preiaSetare("dimensiune_harta") << "\n";
        std::cout << "Setare booleana test: " << (cfg.preiaSetareBool("debug_mode") ? "true" : "false") << "\n";
    } catch (const EroareHarta& e) {
        std::cout << "Exceptie prinsa: " << e.what() << "\n";
        std::cout << "[INFO] Se folosesc setari implicite.\n";
    }

    std::cout << "\n===== DEMO: BIBLIOTECA EXTERNA JSON =====\n";
    try {
        std::ifstream jsonFile("assets/config_joc.json");
        if (jsonFile.is_open()) {
            nlohmann::json jsonData = nlohmann::json::parse(jsonFile);
            std::cout << "Joc: " << jsonData["joc"]["nume"].get<std::string>()
                      << " v" << jsonData["joc"]["versiune"].get<std::string>() << "\n";
            std::cout << "Dimensiune harta (JSON): " << jsonData["joc"]["dimensiune_harta"].get<int>() << "\n";
            std::cout << "Energie initiala (JSON): " << jsonData["joc"]["energie_initiala"].get<int>() << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Eroare JSON: " << e.what() << "\n";
    }

    std::cout << "\n===== OBIECTE SI INVENTAR =====\n";
    Obiect b1("Baterie Duracell", 20, 'B');
    Obiect b2("Teleportor", 0, 'P');
    std::cout << b1 << "\n" << b2 << "\n";

    Inventar inv(4);
    inv.adauga(b1);
    inv.adauga(b2);
    inv.adauga(Obiect("Elixir", 30, 'E'));
    inv.afiseazaInventar();
    std::cout << inv << "\n";
    std::cout << "Dimensiune inventar: " << inv.dimensiune() << "\n";
    std::cout << "Capacitate inventar: " << inv.capacitate() << "\n";

    std::cout << "\n===== IERARHIE INAMICI (3 DERIVATE) =====\n";

    Harta hDemo(8);
    Jucator jDemo(1, 1, 50);

    const auto& grila = hDemo.preiaGrila();
    std::cout << "Dimensiune grila: " << grila.size() << "x" << (grila.empty() ? 0 : grila[0].size()) << "\n";
    jDemo.incarcaEnergie(10);
    std::cout << "Energie dupa incarcare: " << jDemo.preiaEnergie() << "\n";
    jDemo.afiseazaStatusInventar();

    std::vector<std::unique_ptr<VanatorAI>> inamiciDemo;
    inamiciDemo.push_back(std::make_unique<Chaser>(4, 3));
    inamiciDemo.push_back(std::make_unique<Fantoma>(5, 5));
    inamiciDemo.push_back(std::make_unique<Gardian>(3, 6, 4));

    inamiciDemo[0]->reseteazaPozitie(2, 2);
    std::cout << "Dupa reset: (" << inamiciDemo[0]->preiaX() << ", " << inamiciDemo[0]->preiaY() << ")\n";

    for (auto& inamic : inamiciDemo) {
        std::cout << *inamic << "\n";
        inamic->muta(jDemo, hDemo);
        std::cout << "  Dupa mutare: (" << inamic->preiaX() << ", " << inamic->preiaY() << ")\n";
        auto clona = inamic->clone();
        std::cout << "  Clona: " << *clona << "\n";
    }

    std::cout << "\n===== DYNAMIC_CAST DEMO =====\n";
    for (auto& inamic : inamiciDemo) {
        const VanatorAI* ptr = inamic.get();
        if (const auto* g = dynamic_cast<const Gardian*>(ptr)) {
            std::cout << "  Este Gardian! Simbol: " << g->preiaSimbol()
                      << " | Strategie: " << g->strategieVanatoare() << "\n";
        } else if (const auto* c = dynamic_cast<const Chaser*>(ptr)) {
            std::cout << "  Este Chaser! Simbol: " << c->preiaSimbol()
                      << " | Strategie: " << c->strategieVanatoare() << "\n";
        } else if (const auto* f = dynamic_cast<const Fantoma*>(ptr)) {
            std::cout << "  Este Fantoma! Simbol: " << f->preiaSimbol()
                      << " | Strategie: " << f->strategieVanatoare() << "\n";
        }
    }

    std::cout << "\n===== FACTORY INAMICI (Design Pattern) =====\n";
    try {
        auto inamic1 = FactoryInamici::creeazaInamic("chaser", 2, 2);
        auto inamic2 = FactoryInamici::creeazaInamic("gardian", 5, 5, 6);
        auto inamic3 = FactoryInamici::creeazaTip<Fantoma>(3, 3);
        std::cout << "Creat prin Factory: " << *inamic1 << "\n";
        std::cout << "Creat prin Factory: " << *inamic2 << "\n";
        std::cout << "Creat prin Factory (template): " << *inamic3 << "\n";
    } catch (const EroareJucator& e) {
        std::cout << "Exceptie Factory: " << e.what() << "\n";
    }

    std::cout << "\n===== CLASA SABLON ManagementResurse<T> =====\n";

    ManagementResurse<Obiect> mgrObiecte;
    mgrObiecte.adauga(Obiect("Sabie", 10, 'S'));
    mgrObiecte.adauga(Obiect("Scut", 5, 'H'));
    mgrObiecte.adauga(Obiect("Potiune", 15, 'P'));
    mgrObiecte.adauga(Obiect("Amuleta", 8, 'A'));
    std::cout << mgrObiecte;

    std::cout << "Este gol? " << (mgrObiecte.gol() ? "Da" : "Nu") << "\n";
    std::cout << "Primul element (preia): " << mgrObiecte.preia(0) << "\n";
    std::cout << "Toate elementele (preiaToate): " << mgrObiecte.preiaToate().size() << "\n";

    mgrObiecte.sorteaza([](const Obiect& a, const Obiect& b) {
        return a.preiaBonus() > b.preiaBonus();
    });
    std::cout << "Dupa sortare (bonus desc):\n" << mgrObiecte;

    auto puternice = mgrObiecte.filtreaza([](const Obiect& o) {
        return o.preiaBonus() >= 10;
    });
    std::cout << "Obiecte puternice (bonus >= 10): " << puternice.size() << "\n";

    mgrObiecte.sterge(mgrObiecte.dimensiune() - 1);
    std::cout << "Dupa stergere ultimul: dimensiune=" << mgrObiecte.dimensiune() << "\n";

    ManagementResurse<Obiect> mgrTemp;
    mgrTemp.adaugaMultiple({Obiect("X", 1, 'X'), Obiect("Y", 2, 'Y')});
    std::cout << "Adaugate multiplu: " << mgrTemp.dimensiune() << "\n";
    mgrTemp.goleste();

    ManagementResurse<int> mgrScoruri;
    mgrScoruri.adauga(100);
    mgrScoruri.adauga(45);
    mgrScoruri.adauga(230);
    mgrScoruri.adauga(78);
    std::cout << "Scoruri: " << mgrScoruri;
    mgrScoruri.sorteaza([](int a, int b) { return a > b; });
    std::cout << "Scoruri sortate desc:\n" << mgrScoruri;

    std::vector<int> scoruriRaw = {100, 45, 230, 78};
    int maxScor = gasesteMaxim<int>(scoruriRaw, [](int a, int b) { return a > b; });
    std::cout << "Scor maxim: " << maxScor << "\n";

    std::vector<std::string> numeRaw = {"Alice", "Zoe", "Bob", "Charlie"};
    auto maxNume = gasesteMaxim<std::string>(numeRaw,
        [](const std::string& a, const std::string& b) { return a > b; });
    std::cout << "Nume maxim lexicografic: " << maxNume << "\n";

    std::cout << "\n===== IERARHIE EXCEPTII =====\n";

    try {
        throw EroareHarta("Dimensiunea hartii este prea mica");
    } catch (const EroareJoc& e) {
        std::cout << "Prins (EroareJoc): " << e.what() << "\n";
    }

    try {
        ManagementResurse<int> test;
        test.preia(999);
    } catch (const EroareInventar& e) {
        std::cout << "Prins (EroareInventar): " << e.what() << "\n";
    }

    try {
        throw EroareJucator("Energie insuficienta");
    } catch (const EroareJucator& e) {
        std::cout << "Prins (EroareJucator): " << e.what() << "\n";
    }

    std::cout << "\n===== MEMBRU STATIC =====\n";
    std::cout << "Numar total jocuri create: " << MotorJoc::preiaNumarTotalJocuri() << "\n";

    std::cout << "\n===== PORNIRE JOC =====\n";
    try {
        int dim = ConfiguratorJoc::preiaInstanta().preiaSetareInt("dimensiune_harta", 13);
        if (dim < 5 || dim > 30) {
            throw EroareHarta("Dimensiunea hartii trebuie sa fie intre 5 si 30");
        }

        MotorJoc joc(dim);
        std::cout << "Jocuri create pana acum: " << MotorJoc::preiaNumarTotalJocuri() << "\n";
        joc.ruleazaJoc();

    } catch (const EroareJoc& e) {
        std::cerr << "Eroare fatala: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Eroare standard: " << e.what() << "\n";
        return 2;
    }

    std::cout << "\n===== LA REVEDERE! =====\n";
    return 0;
}
