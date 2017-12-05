//
// Created by adire on 05-Dec-17.
//

#include "Stimulant.h"

Stimulant::Stimulant(int code, int factor, int num_of_gladiators) : code(code), factor(factor), i(0), j(0), num_of_gladiators(num_of_gladiators){
    factored_gladiators = new GladiatorLevel [num_of_gladiators];
    non_factored_gladiators = new GladiatorLevel [num_of_gladiators];
}

Stimulant::Stimulant(const Stimulant& stimulant) : code(stimulant.code),factor(stimulant.factor), i(stimulant.i), j(stimulant.j) {
    factored_gladiators = new GladiatorLevel [stimulant.num_of_gladiators];
    non_factored_gladiators = new GladiatorLevel [stimulant.num_of_gladiators];
}

Stimulant::~Stimulant() {
    delete[] factored_gladiators;
    delete[] non_factored_gladiators;
}

void Stimulant::operator()(GladiatorLevel *gladiator) {
    if (gladiator->getID() % code == 0) {
        GladiatorLevel gladiatorLevel(gladiator->getID(), gladiator->getLevel()*factor);
        factored_gladiators[i] = gladiatorLevel;
        i++;
    } else {
        non_factored_gladiators[j] = *gladiator;
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
        if ((stimulantLevel.factored_gladiators[j] < stimulantLevel.non_factored_gladiators[k] && stimulantLevel.factored_gladiators[j].getID() != -1) ||
            stimulantLevel.non_factored_gladiators[k].getID() == -1) {
            trainer->gladiators->insert(stimulantLevel.factored_gladiators[j]);
            j++;
        } else {
            trainer->gladiators->insert(stimulantLevel.non_factored_gladiators[k]);
            k++;
        }
    }
}