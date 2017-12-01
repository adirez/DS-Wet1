//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_TRAINER_H
#define WET1_TRAINER_H

#include "SplayTree.h"
#include "Colosseum.h"
#include "Gladiator.h"

class Trainer {
private:
    int id;
    SplayTree<GladiatorLevel*> gladiators;

    friend class Colosseum;
    friend class StimulantTrainers;
public:
    explicit Trainer(int id);
    ~Trainer() {};
    bool operator<(const Trainer &trainer2) const;
    bool operator>(const Trainer &trainer2) const;
    bool operator==(const Trainer &trainer2) const;
    bool operator!=(const Trainer &trainer2) const;
};


#endif //WET1_TRAINER_H
