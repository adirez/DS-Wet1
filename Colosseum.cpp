//
// Created by adire on 30-Nov-17.
//

#include "Colosseum.h"
#include <cstdlib>

class GladiatorsByLevel {
private:
    int index;
    int size;
    int **gladiators_ids;

    friend class Colosseum;

public:
    GladiatorsByLevel(int size, int **gladiators_ids) : index(0), size(size), gladiators_ids(gladiators_ids){
        *this->gladiators_ids = (int *) malloc(size * sizeof(int));
        if (NULL == *this->gladiators_ids) {
            throw MemoryProblem();
        }
    }

    ~GladiatorsByLevel() {
    } //we don't want the default destructor so it will not delete the array
    void operator()(const GladiatorLevel *gladiator) {
        (*gladiators_ids)[index] = gladiator->getID();
        index++;
    }
};

class StimulantID {
private:
    int stimulant_code;
    int stimulant_factor;
    GladiatorID *gladiators1;
    GladiatorID *gladiators2;
    int i;
    int j;

    friend class Colosseum;

public:
    StimulantID(int stimulant_code, int stimulant_factor, int num_of_gladiators) : stimulant_code(stimulant_code),
                                                                                 stimulant_factor(stimulant_factor),
                                                                                 i(0), j(0){
        gladiators1 = new GladiatorID [num_of_gladiators];
        gladiators2 = new GladiatorID [num_of_gladiators];
    }

    ~StimulantID() {
        delete[] gladiators1;
        delete[] gladiators2;
    }

    void operator()(GladiatorID *gladiator) {
        if (gladiator->getID() % stimulant_code == 0) {
            GladiatorID gladiatorID(gladiator->getID(), gladiator->getLevel()*stimulant_factor, gladiator->getTrainerPtr());
            gladiators1[i] = gladiatorID;
            i++;
        } else {
            gladiators2[j] = *gladiator;
            j++;
        }
    }
};

class StimulantLevel {
private:
    int stimulant_code;
    int stimulant_factor;
    GladiatorLevel *gladiators1;
    GladiatorLevel *gladiators2;
    int i;
    int j;
    int num_of_gladiators;

    friend class Colosseum;
    friend class StimulantTrainers;

public:
    StimulantLevel(int stimulant_code, int stimulant_factor, int num_of_gladiators) : stimulant_code(stimulant_code),
                                                                                   stimulant_factor(stimulant_factor),
                                                                                   i(0), j(0), num_of_gladiators(num_of_gladiators){
        gladiators1 = new GladiatorLevel [num_of_gladiators];
        gladiators2 = new GladiatorLevel [num_of_gladiators];
    }
    StimulantLevel(const StimulantLevel& stimulantLevel) : stimulant_code(stimulantLevel.stimulant_code),
                                                           stimulant_factor(stimulantLevel.stimulant_factor),
                                                           i(stimulantLevel.i), j(stimulantLevel.j) {
        gladiators1 = new GladiatorLevel [stimulantLevel.num_of_gladiators];
        gladiators2 = new GladiatorLevel [stimulantLevel.num_of_gladiators];
    }

    ~StimulantLevel() {
        delete[] gladiators1;
        delete[] gladiators2;
    }

    void operator()(GladiatorLevel *gladiator) {
        if (gladiator->getID() % stimulant_code == 0) {
            GladiatorLevel gladiatorLevel(gladiator->getID(), gladiator->getLevel()*stimulant_factor);
            gladiators1[i] = gladiatorLevel;
            i++;
        } else {
            gladiators2[j] = *gladiator;
            j++;
        }
    }
};


class StimulantTrainers {
private:
    StimulantLevel *stimulant;
public:
    explicit StimulantTrainers(StimulantLevel *stimulant) : stimulant(stimulant) {}

    ~StimulantTrainers() {}

    void operator()(Trainer *trainer) {
        StimulantLevel stimulantLevel(*stimulant);
        int size = trainer->gladiators->getSize();
        trainer->gladiators->inOrder(stimulantLevel);
        delete trainer->gladiators;
        trainer->gladiators = new SplayTree<GladiatorLevel>;
        int j = 0, k = 0;
        for (int i = 0; i < size; ++i) {
            if ((stimulantLevel.gladiators1[j] < stimulantLevel.gladiators2[k] && stimulantLevel.gladiators1[j].getID() != -1) ||
                    stimulantLevel.gladiators2[k].getID() == -1) {
                trainer->gladiators->insert(stimulantLevel.gladiators1[j]);
                j++;
            } else {
                trainer->gladiators->insert(stimulantLevel.gladiators2[k]);
                k++;
            }
        }
    }
};

Colosseum::Colosseum() : num_gladiators(0), num_trainers(0) {
    gladiators_id_tree = new SplayTree<GladiatorID>;
    gladiators_level_tree = new SplayTree<GladiatorLevel>;
    trainers_tree = new SplayTree<Trainer>;
}

Colosseum::~Colosseum() {
    delete gladiators_id_tree;
    delete gladiators_level_tree;
    delete trainers_tree;
}

void Colosseum::addTrainer(int trainer_id) {
    if (trainer_id <= 0) {
        throw InvalidParameter();
    }
    trainers_tree->insert(Trainer(trainer_id));
    num_trainers++;
}

//Time complexity: log(n) + log(k)
void Colosseum::buyGladiator(int gladiator_id, int trainer_id, int level) {
    if (gladiator_id <= 0 || trainer_id <= 0 || level <= 0) {
        throw InvalidParameter();
    }
    GladiatorID gladiatorID(gladiator_id, level);
    GladiatorLevel gladiatorLevel(gladiator_id, level);
    Trainer trainer(trainer_id);

    Trainer *trainer_ptr = &(trainers_tree->find(trainer)); //log(k)

    gladiators_id_tree->insert(gladiatorID); //log(n)
    trainer_ptr->gladiators->insert(gladiatorLevel); //log(n)
    gladiators_level_tree->insert(gladiatorLevel); //log(n)
    gladiators_id_tree->find(gladiatorID).setTrainerPtr(trainer_ptr); //1 (after insertion the gladiator is in the root)
    num_gladiators++;
}

void Colosseum::freeGladiator(int gladiator_id) {
    if (gladiator_id <= 0) {
        throw InvalidParameter();
    }
    GladiatorID to_delete = gladiators_id_tree->find(GladiatorID(gladiator_id, 0));
    gladiators_level_tree->remove(GladiatorLevel(gladiator_id, to_delete.getLevel()));
    Trainer *trainer = to_delete.getTrainerPtr();
    trainer->gladiators->remove(GladiatorLevel(gladiator_id, to_delete.getLevel()));
    gladiators_id_tree->remove(to_delete);
    num_gladiators--;
}

void Colosseum::levelUp(int gladiator_id, int level_inc) {
    if (gladiator_id <= 0 || level_inc <= 0) {
        throw InvalidParameter();
    }
    GladiatorID gladiator_by_id = gladiators_id_tree->find(GladiatorID(gladiator_id, 0));
    gladiators_level_tree->remove(GladiatorLevel(gladiator_id, gladiator_by_id.getLevel()));
    gladiator_by_id.getTrainerPtr()->gladiators->remove(GladiatorLevel(gladiator_id, gladiator_by_id.getLevel()));

    Trainer *ptr_to_trainer = gladiator_by_id.getTrainerPtr();
    int new_level = gladiator_by_id.getLevel() + level_inc;
    gladiators_id_tree->remove(GladiatorID(gladiator_id, 0));

    gladiators_id_tree->insert(GladiatorID(gladiator_id, new_level, ptr_to_trainer));
    gladiators_level_tree->insert(GladiatorLevel(gladiator_id, new_level));
    gladiator_by_id.getTrainerPtr()->gladiators->insert(GladiatorLevel(gladiator_id, new_level));
}

int Colosseum::getTopGladiator(int trainer_id) {
    if (trainer_id < 0) {
        return gladiators_level_tree->getMax().getID();
    }
    if(gladiators_id_tree->getSize() == 0){
        throw EmptyTree();
    }
    if(trainers_tree->find(Trainer(trainer_id)).gladiators->getSize() == 0){
        return -1;
    }
    return trainers_tree->find(Trainer(trainer_id)).gladiators->getMax().getID();
}

void Colosseum::getAllGladiatorsByLevel(int trainer_id, int *numOfGladiators, int **gladiators) {
    if (trainer_id < 0) {
        *numOfGladiators = num_gladiators;
        if (*numOfGladiators == 0) {
            *gladiators = NULL;
            return;
        }
        GladiatorsByLevel gladiatorsByLevel(*numOfGladiators, gladiators);
        gladiators_level_tree->inOrderReverse(gladiatorsByLevel);
        return;
    }
    *numOfGladiators = trainers_tree->find(Trainer(trainer_id)).gladiators->getSize();
    if (*numOfGladiators == 0) {
        *gladiators = NULL;
        return;
    }
    GladiatorsByLevel gladiatorsByLevel(*numOfGladiators, gladiators);
    trainers_tree->find(Trainer(trainer_id)).gladiators->inOrderReverse(gladiatorsByLevel);
}

void Colosseum::updateGladiator(int gladiator_id, int upgrade_id) {
    if (gladiator_id <= 0 || upgrade_id <= 0) {
        throw InvalidParameter();
    }
    try {
        gladiators_id_tree->find(GladiatorID(upgrade_id, 0));
    } catch (KeyNotFound &e) {
        GladiatorID to_upgrade = gladiators_id_tree->find(GladiatorID(gladiator_id, 0));
        int level = to_upgrade.getLevel();
        Trainer *trainer = to_upgrade.getTrainerPtr();
        gladiators_level_tree->remove(GladiatorLevel(gladiator_id, level));
        gladiators_level_tree->insert(GladiatorLevel(upgrade_id, level));
        trainer->gladiators->remove(GladiatorLevel(gladiator_id, level));
        trainer->gladiators->insert(GladiatorLevel(upgrade_id, level));
        gladiators_id_tree->remove(to_upgrade);
        gladiators_id_tree->insert(GladiatorID(upgrade_id, level, trainer));
        return;
    }
    throw KeyAlreadyExists();
}

void Colosseum::updateLevels(int stimulantCode, int stimulantFactor) {
    if (stimulantCode < 1 || stimulantFactor < 1) {
        throw InvalidParameter();
    }
    StimulantID stimulantID(stimulantCode, stimulantFactor, num_gladiators);
    gladiators_id_tree->inOrder(stimulantID);
    delete gladiators_id_tree;
    gladiators_id_tree = new SplayTree<GladiatorID>;
    int j = 0, k = 0;
    for (int i = 0; i < num_gladiators; ++i) {
        if ((stimulantID.gladiators1[j] < stimulantID.gladiators2[k] && stimulantID.gladiators1[j].getID() != -1) ||
                stimulantID.gladiators2[k].getID() == -1) {
            gladiators_id_tree->insert(stimulantID.gladiators1[j]);
            j++;
        } else {
            gladiators_id_tree->insert(stimulantID.gladiators2[k]);
            k++;
        }
    }

    StimulantLevel stimulantLevel(stimulantCode, stimulantFactor, num_gladiators);
    gladiators_level_tree->inOrder(stimulantLevel);
    delete gladiators_level_tree;
    gladiators_level_tree = new SplayTree<GladiatorLevel>;
    j = 0, k = 0;
    for (int i = 0; i < num_gladiators; ++i) {
        if ((stimulantLevel.gladiators1[j] < stimulantLevel.gladiators2[k] && stimulantLevel.gladiators1[j].getID() != -1) ||
                stimulantLevel.gladiators2[k].getID() == -1)  {
            gladiators_level_tree->insert(stimulantLevel.gladiators1[j]);
            j++;
        } else {
            gladiators_level_tree->insert(stimulantLevel.gladiators2[k]);
            k++;
        }
    }

    StimulantLevel stimulantLevel2(stimulantCode, stimulantFactor, num_gladiators);
    StimulantTrainers stimulantTrainers(&stimulantLevel2);
    trainers_tree->inOrder(stimulantTrainers);
}





