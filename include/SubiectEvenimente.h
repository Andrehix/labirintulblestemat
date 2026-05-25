#ifndef SUBIECT_EVENIMENTE_H
#define SUBIECT_EVENIMENTE_H

#include "ObserverJoc.h"
#include <vector>
#include <memory>

class SubiectEvenimente {
private:
    std::vector<ObserverJoc*> observatori;

public:
    void adaugaObservator(ObserverJoc* obs) {
        observatori.push_back(obs);
    }

    void notificaObservatori(const std::string& eveniment) {
        for (auto* obs : observatori) {
            obs->notifica(eveniment);
        }
    }
};

#endif
