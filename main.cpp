#include <iostream>
#include <memory>
#include "include/MotorJoc.h"
#include "include/ConfiguratorJoc.h"
#include "include/Exceptii.h"
#include "include/LoggerJoc.h"

int main() {
    std::cout << "=== PROIECT: JOC LABIRINT OOP ===\n";
    LoggerJoc logger;

    ConfiguratorJoc& cfg = ConfiguratorJoc::preiaInstanta();
    try {
        cfg.incarcaDinFisier("assets/config_joc.txt");
        cfg.afiseazaSetari();
    } catch (const EroareFisierLipsa& e) {
        std::cout << "[AVERTISMENT] " << e.what() << "\nSe folosesc setarile default.\n";
    } catch (const EroareFormatFisier& e) {
        std::cout << "[EROARE FORMAT] " << e.what() << "\n";
    } catch (const EroareInitializare& e) {
        std::cout << "[EROARE INIT] " << e.what() << "\n";
    } catch (const EroareJoc& e) {
        std::cout << "[EROARE JOC] " << e.what() << "\n";
        return 1;
    }

    try {
        int dim = cfg.preiaSetareInt("dimensiune_harta", 10);
        MotorJoc motor(dim);
        motor.adaugaObservator(&logger);
        
        motor.ruleazaJoc();
    } catch (const EroareActiuneInvalida& e) {
        std::cout << "[EROARE LOGICA] " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "[EROARE FATALA] " << e.what() << "\n";
    }

    std::cout << "Evenimente logger: " << logger.numarEvenimente() << "\n";
    std::cout << "Jocuri create: " << MotorJoc::preiaNumarTotalJocuri() << "\n";
    return 0;
}
