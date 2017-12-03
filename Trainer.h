//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_TRAINER_H
#define WET1_TRAINER_H

#include "SplayTree.h"
#include "GladiatorLevel.h"

class Trainer {
private:
    int id;
    SplayTree<GladiatorLevel> *gladiators;
    Trainer &operator=(const Trainer &trainer);

    friend class Colosseum;
    friend class StimulantTrainers;

    friend bool operator==(const Trainer &trainer1, const Trainer &trainer2);
    friend bool operator!=(const Trainer &trainer1, const Trainer &trainer2);
public:
    explicit Trainer(int id);
    ~Trainer();
    int getID();
    bool operator<(const Trainer &trainer2) const;
    bool operator>(const Trainer &trainer2) const;

    Trainer(const Trainer& trainer);
};

bool operator==(const Trainer &trainer1, const Trainer &trainer2);
bool operator!=(const Trainer &trainer1, const Trainer &trainer2);

#endif //WET1_TRAINER_H
