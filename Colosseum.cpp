//
// Created by adire on 30-Nov-17.
//

#include "Colosseum.h"
#include <cstdlib>

/**
 * a function object to be used in getAllGladiatorsByLevel.
 * contains the size (number of gladiators to return), the index of the current gladiator to return and a pointer to the array.
 */
class GladiatorsByLevel {
private:
    int index;
    int size;
    int **gladiators_ids;

    friend class Colosseum;

public:
    /**
     * constructor for the function object. receiving the parameters and allocating the array for the gladiators according to the pointer received.
     * the constructor only allocates the memory so it runs on time complexity of O(1).
     * @param size - the size of the array to allocate for the gladiators
     * @param gladiators_ids - a pointer for the array to allocate
     */
    GladiatorsByLevel(int size, int **gladiators_ids) : index(0), size(size), gladiators_ids(gladiators_ids){
        *this->gladiators_ids = (int *) malloc(size * sizeof(int));
        if (NULL == *this->gladiators_ids) {
            throw MemoryProblem();
        }
    }

    /**
     * an empty destructor so it will not release the memory allocated for the array (since it is the output). the destructor is empty so it runs on
     * time complexity of O(1).
     */
    ~GladiatorsByLevel() {
    } //we don't want the default destructor so it will not delete the array

    /**
     * the operator sent to inOrder at getAllGladiatorsByLevel function. the action will be done through operator(). each gladiator sent to () will be
     * copied to the allocated array and increase the index. the function only used getID and copies an ID of a single gladiator and thus runs in a
     * time complexity of O(1).
     * @param gladiator - the gladiator found at inOrder which will be copied to the array
     */
    void operator()(const GladiatorLevel *gladiator) {
        (*gladiators_ids)[index] = gladiator->getID();
        index++;
    }
};

/**
 * a function object to be used in Stimulant for gladiators of type GladiatorID.
 * contains the stimulant code and factor to operate with, two arrays to which we will sort the gladiators (one for those who have used the drug and
 * one for those who haven't) and index for each of the arrays.
 */
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
    /**
     * a constructor for the function object. receiving the parameters and allocating the arrays to which we will sort the gladiators by the stimulant
     * code. index i and index j are initialized to 0 in order to start from the beginning of the arrays. the constructor only allocates arrays and
     * thus runs in a time complexity of O(1).
     * @param stimulant_code - the code to check the gladiators by
     * @param stimulant_factor - the factor to increase the level of the relevant gladiators by
     * @param num_of_gladiators - the number of gladiators to sort
     */
    StimulantID(int stimulant_code, int stimulant_factor, int num_of_gladiators) : stimulant_code(stimulant_code),
                                                                                 stimulant_factor(stimulant_factor),
                                                                                 i(0), j(0){
        gladiators1 = new GladiatorID [num_of_gladiators];
        gladiators2 = new GladiatorID [num_of_gladiators];
    }

    /**
     * a destructor for the function object. deletes both of the allocated arrays. the destructor only deletes two arrays and thus runs in a time
     * complexity of O(1).
     */
    ~StimulantID() {
        delete[] gladiators1;
        delete[] gladiators2;
    }

    /**
     * the operator sent to inOrder by Stimulant function. the action will be done through operator(). each gladiator sent to () will be
     * checked with the stimulant code and according to that sent to the relevant allocated array and increase the relevant index. the gladiators sent
     * to the first array are the ones that have been using the drug and therefore their level will be increased according to the factor. the function
     * calls a constructor and uses 'get' functions and thus runs in a time complexity of O(1).
     * @param gladiator - the gladiator found at inOrder which will be copied to one of the arrays
     */
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

/**
 * a function object to be used in Stimulant for gladiators of type GladiatorLevel.
 * contains the stimulant code and factor to operate with, two arrays to which we will sort the gladiators (one for those who have used the drug and
 * one for those who haven't) and index for each of the arrays.
 */
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
    /**
     * a constructor for the function object. receiving the parameters and allocating the arrays to which we will sort the gladiators by the stimulant
     * code. index i and index j are initialized to 0 in order to start from the beginning of the arrays. the constructor only allocates arrays and
     * thus runs in a time complexity of O(1).
     * @param stimulant_code - the code to check the gladiators by
     * @param stimulant_factor - the factor to increase the level of the relevant gladiators by
     * @param num_of_gladiators - the number of gladiators to sort
     */
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

    /**
     * a destructor for the function object. deletes both of the allocated arrays. the destructor only deletes two arrays and thus runs in a time
     * complexity of O(1).
     */
    ~StimulantLevel() {
        delete[] gladiators1;
        delete[] gladiators2;
    }

    /**
     * the operator sent to inOrder by Stimulant function. the action will be done through operator(). each gladiator sent to () will be
     * checked with the stimulant code and according to that sent to the relevant allocated array and increase the relevant index. the gladiators sent
     * to the first array are the ones that have been using the drug and therefore their level will be increased according to the factor. the function
     * calls a constructor and uses 'get' functions and thus runs in a time complexity of O(1).
     * @param gladiator - the gladiator found at inOrder which will be copied to one of the arrays
     */
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

/**
 * a function object to be used in Stimulant for trainers to sort gladiators of type GladiatorLevel. receives as a parameter the function object of
 * GladiatorLevel since the gladiators in the trainers' tree are of type GladiatorLevel. the function goes through a trainer at a time and for each
 * trainer summons StimulantLevel for the tree in order to sort it's own tree of gladiators.
 */
class StimulantTrainers {
private:
    StimulantLevel *stimulant;
public:

    /**
     * a constructor for the function object. receives a StimulantLevel in order to summon for each of the trainers for their own trees of gladiators.
     * @param stimulant - the function object called for the trainers' trees
     */
    explicit StimulantTrainers(StimulantLevel *stimulant) : stimulant(stimulant) {}

    /**
     * empty destructor for the function object
     */
    ~StimulantTrainers() {}

    /**
     * the operator sent to inOrder by Stimulant function. the action will be done through operator(). each trainer sent to () will have it's
     * gladiators tree sent to stimulant compatible for GladiatorLevel. the tree will then be checked with the stimulant code and according to
     * that gladiators will be sent to the relevant allocated array and increase the relevant index of StimulantLevel. StimulantLevel runs in a time
     * complexity of O(1) per single gladiator. therefore, in the worst case scenario a trainer will have 'n' gladiators and thus the function will
     * run in a time complexity of O(n).
     * @param trainer - the trainer whose tree will be sent to StimulateLevel
     */
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
    trainers_tree->insert(Trainer(trainer_id)); //log(k)
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
    GladiatorID to_delete = gladiators_id_tree->find(GladiatorID(gladiator_id, 0)); //log(n)
    gladiators_level_tree->remove(GladiatorLevel(gladiator_id, to_delete.getLevel())); //log(n)
    Trainer *trainer = to_delete.getTrainerPtr();
    trainer->gladiators->remove(GladiatorLevel(gladiator_id, to_delete.getLevel())); //log(n)
    gladiators_id_tree->remove(to_delete); //log(n)
    num_gladiators--;
}

void Colosseum::levelUp(int gladiator_id, int level_inc) {
    if (gladiator_id <= 0 || level_inc <= 0) {
        throw InvalidParameter();
    }
    GladiatorID gladiator_by_id = gladiators_id_tree->find(GladiatorID(gladiator_id, 0)); //log(n)
    gladiators_level_tree->remove(GladiatorLevel(gladiator_id, gladiator_by_id.getLevel())); //log(n)
    gladiator_by_id.getTrainerPtr()->gladiators->remove(GladiatorLevel(gladiator_id, gladiator_by_id.getLevel())); //log(n)

    Trainer *ptr_to_trainer = gladiator_by_id.getTrainerPtr();
    int new_level = gladiator_by_id.getLevel() + level_inc;
    gladiators_id_tree->remove(GladiatorID(gladiator_id, 0)); //log(n)

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





