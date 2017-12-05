//
// Created by adire on 05-Dec-17.
//

#include "Stimulant.h"

Stimulant::Stimulant(int code, int factor, int num_of_gladiators) : code(code), factor(factor), i(0), j(0), num_of_gladiators(num_of_gladiators){
    gladiators1 = new GladiatorLevel [num_of_gladiators];
    gladiators2 = new GladiatorLevel [num_of_gladiators];
}

Stimulant::Stimulant(const Stimulant& stimulant) : code(stimulant.code), factor(stimulant.factor), i(stimulant.i), j(stimulant.j), num_of_gladiators(stimulant.num_of_gladiators) {
    gladiators1 = new GladiatorLevel [stimulant.num_of_gladiators];
    gladiators2 = new GladiatorLevel [stimulant.num_of_gladiators];
}

Stimulant::~Stimulant() {
    delete[] gladiators1;
    delete[] gladiators2;
}

void Stimulant::operator()(GladiatorLevel *gladiator) {
    if (gladiator->getID() % code == 0) {
        GladiatorLevel gladiatorLevel(gladiator->getID(), gladiator->getLevel()*factor);
        gladiators1[i] = gladiatorLevel;
        i++;
    } else {
        gladiators2[j] = *gladiator;
        j++;
    }
}




void StimulantTrainers::operator()(Trainer *trainer) {
    Stimulant stimulantLevel(*stimulant);
    int size = trainer->gladiators->getSize();
    trainer->gladiators->inOrder(stimulantLevel);
    delete trainer->gladiators;
    trainer->gladiators = new SplayTree<GladiatorLevel>;
    int j = 0, k = 0;
    for (int i = 0; i < size; ++i) {
        if ((stimulant->gladiators1[j] < stimulant->gladiators2[k] && stimulant->gladiators1[j].getID() != -1) ||
            stimulant->gladiators2[k].getID() == -1)  {
            trainer->gladiators->insert(stimulant->gladiators1[j]);
            j++;
        } else {
            trainer->gladiators->insert(stimulant->gladiators2[k]);
            k++;
        }
    }
}