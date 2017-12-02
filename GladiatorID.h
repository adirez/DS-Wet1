//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATORID_H
#define WET1_GLADIATORID_H

#include "Gladiator.h"
#include "Trainer.h"

class GladiatorID : public Gladiator {
private:
    Trainer *ptr_to_trainer;

    friend class Colosseum;
public:
    GladiatorID(int id, int level, Trainer *ptr_to_trainer);
    GladiatorID(int id, int level);
    ~GladiatorID() {};
    GladiatorID(const GladiatorID& gladiator);
    int getID() const;
    int getLevel() const;
    Trainer* getTrainerPtr() const;
    bool operator<(const Gladiator &gladiator2) const;
    bool operator>(const Gladiator &gladiator2) const;
};


#endif //WET1_GLADIATORID_H
