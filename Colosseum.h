//
// Created by adire on 30-Nov-17.
//

#ifndef WET1_COLOSSEUM_H
#define WET1_COLOSSEUM_H

#include "GladiatorID.h"
#include "GladiatorLevel.h"

class Colosseum {
private:
    int num_gladiators;
    int num_trainers;
    SplayTree<GladiatorID> *gladiators_id_tree;
    SplayTree<GladiatorLevel> *gladiators_level_tree;
    SplayTree<Trainer> *trainers_tree;

    Colosseum(const Colosseum &colosseum);
    Colosseum &operator=(const Colosseum &colosseum);

public:
    Colosseum();
    ~Colosseum();
    void addTrainer(int trainer_id);
    void buyGladiator(int gladiator_id, int trainer_id, int level);
    void freeGladiator(int gladiator_id);
    void levelUp(int gladiator_id, int level_inc);
    int getTopGladiator(int trainer_id);
    void getAllGladiatorsByLevel(int trainer_id, int *numOfGladiators, int **gladiators);
    void updateGladiator(int gladiator_id, int upgrade_id);
    void updateLevels(int stimulantCode, int stimulantFactor);
};


#endif //WET1_COLOSSEUM_H
