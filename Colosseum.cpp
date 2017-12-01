//
// Created by adire on 30-Nov-17.
//

#include "Colosseum.h"
#include <cstdlib>

class GladiatorsByLevel {
private:
    int index;
    int size;
    int *gladiators_ids;

    friend class Colosseum;
public:
    GladiatorsByLevel(int size, int **gladiators_ids) : index(0), size(size), gladiators_ids(*gladiators_ids) {
       this->gladiators_ids = (int*)malloc(size * sizeof(int));
        if (NULL == this->gladiators_ids) {
            throw MemoryProblem();
        }
    }
    ~GladiatorsByLevel() {} //we don't want the default destructor so it will not delete the array
    void operator()(const Gladiator gladiator) {
        gladiators_ids[index] = gladiator.getID();
        index++;
    }
};

static Gladiator** merge(Gladiator** array1, Gladiator** array2, int size){
    int j = 0, k = 0;
    Gladiator **merged_array = new Gladiator*[size];
    for(int i=0; i < size; ++i){
        if(array1[j] < array2[k]){
            merged_array[i] = array1[j];
            j++;
        } else {
            merged_array[i] = array2[k];
            k++;
        }
    }
    return merged_array;
}

class StimulantTrainers{
private:
    Stimulant stimulant;
public:
    explicit StimulantTrainers(const Stimulant &stimulant) : stimulant(stimulant) {}
    void operator()(const Trainer &trainer) {
        int size = trainer.gladiators->getSize();
        trainer.gladiators->inOrder(stimulant);
        delete trainer.gladiators;
        Gladiator** merged_array = merge(stimulant.gladiators1, stimulant.gladiators2, size);
        for (int i = 0; i < size; ++i) {
            GladiatorLevel *gladiatorLevel = dynamic_cast<GladiatorLevel*>(merged_array[i]);
            trainer.gladiators->insert(*gladiatorLevel);
        }
    }
};

class Stimulant {
private:
    int stimulant_code;
    int stimulant_factor;
    Gladiator **gladiators1;
    Gladiator **gladiators2;
    int i;
    int j;

    friend class Colosseum;
    friend class StimulantTrainers;
public:
    Stimulant(int stimulant_code, int stimulant_factor, int num_of_gladiators) : stimulant_code(stimulant_code),
                                                                                 stimulant_factor(stimulant_factor), i(0), j(0){
        gladiators1 = new Gladiator*[num_of_gladiators];
        gladiators2 = new Gladiator*[num_of_gladiators];
    }
    ~Stimulant() {
        delete gladiators1;
        delete gladiators2;
    }
    void operator()(Gladiator &gladiator) {
        if(gladiator.id % stimulant_code == 0){
            gladiators1[i] = &gladiator;
            i++;
        } else {
            gladiators2[j] = &gladiator;
            j++;
        }
    }
};

Colosseum::Colosseum() : num_gladiators(0), num_trainers(0){
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
    if(trainer_id <= 0){
        throw InvalidParameter();
    }
    trainers_tree->insert(Trainer(trainer_id));
}

void Colosseum::buyGladiator(int gladiator_id, int trainer_id, int level) {
    if(gladiator_id <= 0 || trainer_id <= 0 || level <=0){
        throw InvalidParameter();
    }
    Trainer trainer = trainers_tree->find(Trainer(trainer_id));
    trainer.gladiators->insert(GladiatorLevel(gladiator_id, level));
    gladiators_level_tree->insert(GladiatorLevel(gladiator_id, level));
    gladiators_id_tree->insert(GladiatorID(gladiator_id, level, &trainer));
}

void Colosseum::freeGladiator(int gladiator_id) {
    if(gladiator_id <= 0){
        throw InvalidParameter();
    }
    GladiatorID to_delete = gladiators_id_tree->find(GladiatorID(gladiator_id, 0));
    gladiators_level_tree->remove(GladiatorLevel(gladiator_id, 0));
    Trainer *trainer = to_delete.ptr_to_trainer;
    trainer->gladiators->remove(GladiatorLevel(gladiator_id, 0));
    gladiators_id_tree->remove(to_delete);
}

void Colosseum::levelUp(int gladiator_id, int level_inc) {
    if (gladiator_id <= 0 || level_inc <= 0) {
        throw InvalidParameter();
    }
    GladiatorID gladiator_by_id = gladiators_id_tree->find(GladiatorID(gladiator_id, 0));

    gladiators_level_tree->remove(GladiatorLevel(gladiator_id, 0));
    gladiator_by_id.ptr_to_trainer->gladiators->remove(GladiatorLevel(gladiator_id, 0));
    gladiator_by_id.level += level_inc;

    gladiators_level_tree->insert(GladiatorLevel(gladiator_id, gladiator_by_id.level));
    gladiator_by_id.ptr_to_trainer->gladiators->insert(GladiatorLevel(gladiator_id, gladiator_by_id.level));
}

int Colosseum::getTopGladiator(int trainer_id) {
    if(trainer_id < 0){
        return gladiators_level_tree->getMin().id;
    }
    Trainer trainer = trainers_tree->find(Trainer(trainer_id));
    return trainer.gladiators->getMin().id;
}
void Colosseum::getAllGladiatorsByLevel(int trainer_id, int *numOfGladiators, int **gladiators) {
    if (trainer_id < 0) {
        *numOfGladiators = num_gladiators;
        GladiatorsByLevel gladiatorsByLevel(*numOfGladiators, gladiators);
        gladiators_level_tree->inOrderReverse(gladiatorsByLevel);
        return;
    }

    Trainer trainer = trainers_tree->find(Trainer(trainer_id));
    *numOfGladiators = trainer.gladiators->getSize();
    GladiatorsByLevel gladiatorsByLevel(*numOfGladiators, gladiators);
    trainer.gladiators->inOrderReverse(gladiatorsByLevel);
}

void Colosseum::updateGladiator(int gladiator_id, int upgrade_id) {
    if(gladiator_id <= 0 || upgrade_id <= 0){
        throw InvalidParameter();
    }
    GladiatorID to_upgrade = gladiators_id_tree->find(GladiatorID(gladiator_id, 0));
    int level = to_upgrade.level;
    Trainer *trainer = to_upgrade.ptr_to_trainer;
    gladiators_level_tree->remove(GladiatorLevel(gladiator_id, 0));
    gladiators_level_tree->insert(GladiatorLevel(upgrade_id, level));
    trainer->gladiators->remove(GladiatorLevel(gladiator_id, 0));
    trainer->gladiators->insert(GladiatorLevel(upgrade_id, level));
    gladiators_id_tree->remove(to_upgrade);
    gladiators_id_tree->insert(GladiatorID(upgrade_id, level, trainer));
}

void Colosseum::updateLevels(int stimulantCode, int stimulantFactor) {
    if(stimulantCode < 1 || stimulantFactor < 1){
        throw InvalidParameter();
    }
    Stimulant stimulant(stimulantCode, stimulantFactor, num_gladiators);
    gladiators_id_tree->inOrder(stimulant);
    delete gladiators_id_tree;
    Gladiator** merged_array = merge(stimulant.gladiators1, stimulant.gladiators2, num_gladiators);
    for (int i = 0; i < num_gladiators; ++i) {
        GladiatorID *gladiatorID = dynamic_cast<GladiatorID*>(merged_array[i]);
        gladiators_id_tree->insert(*gladiatorID);
    }

    Stimulant stimulant1(stimulantCode, stimulantFactor, num_gladiators);
    gladiators_level_tree->inOrder(stimulant1);
    delete gladiators_level_tree;
    Gladiator** merged_array1 = merge(stimulant1.gladiators1, stimulant1.gladiators2, num_gladiators);
    for (int i = 0; i < num_gladiators; ++i) {
        GladiatorLevel *gladiatorLevel = dynamic_cast<GladiatorLevel*>(merged_array1[i]);
        gladiators_level_tree->insert(*gladiatorLevel);
    }

    Stimulant stimulant2(stimulantCode, stimulantFactor, num_gladiators);
    StimulantTrainers stimulant_trainers(stimulant2);
}





