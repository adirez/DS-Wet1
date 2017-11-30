//
// Created by adire on 30-Nov-17.
//

#ifndef WET1_COLOSSEUM_H
#define WET1_COLOSSEUM_H

#include "SplayTree.h"

class Colosseum {
private:
    int num_gladiators;
    int num_trainers;
    SplayTree<GladiatorID> gladiators_id_tree;
    SplayTree<GladiatorLevel> gladiators_level_tree;
    SplayTree<Trainer> trainers_tree;

    Colosseum(const Colosseum &colosseum);
    Colosseum &operator=(const Colosseum &colosseum);

public:
    Colosseum();
    void addTrainer(int trainer_id);
    void buyGladiator(int gladiator_id, int trainer_id, int level);
    void freeGladiator(int gladiator_id);
    void levelUp(int gladiator_id, int level_inc);
    int getTopGladiator(int trainer_id);
    int* getAllGladiatorsByLevel(int trainer_id, int *numOfGladiators);
    void updateGladiator(int gladiator_id, int upgrade_id);
    void updateLevels(int stimulantCode, int stimulantFactor);
};

class Gladiator{
public:
    Gladiator() {};
    Gladiator(int id, int level);
    virtual ~Gladiator() {};

protected:
    int id;
    int level;
    virtual bool operator<(const Gladiator &gladiator2) const = 0;
    virtual bool operator>(const Gladiator &gladiator2) const = 0;
    bool operator==(const Gladiator &gladiator2) const;
    bool operator!=(const Gladiator &gladiator2) const;
};

class GladiatorID : public Gladiator{
private:
    GladiatorLevel *ptr_to_level;
    Trainer *ptr_to_trainer;
public:
    GladiatorID(int id, int level, GladiatorLevel *ptr_to_level, Trainer *ptr_to_trainer);
    ~Gladiator() {};
    bool operator<(const Gladiator &gladiator2) const override;
    bool operator>(const Gladiator &gladiator2) const override;
};

class GladiatorLevel : public Gladiator{
public:
    GladiatorLevel(int id, int level);
    ~Gladiator() {};
    bool operator<(const Gladiator &gladiator2) const override;
    bool operator>(const Gladiator &gladiator2) const override;
};

class Trainer {
private:
    int id;
    SplayTree<Gladiator> gladiators;

    friend class Colosseum;
public:
    explicit Trainer(int id);
    ~Trainer() {};
    bool operator<(const Trainer &trainer2) const;
    bool operator>(const Trainer &trainer2) const;
    bool operator==(const Trainer &trainer2) const;
    bool operator!=(const Trainer &trainer2) const;
};

#endif //WET1_COLOSSEUM_H
