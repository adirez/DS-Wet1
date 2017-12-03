//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATORID_H
#define WET1_GLADIATORID_H

#include "Trainer.h"

class GladiatorID {
private:
    int id;
    int level;
    Trainer *trainer_ptr;

    friend bool operator==(const GladiatorID &gladiator1, const GladiatorID &gladiator2);
public:
    GladiatorID();
    GladiatorID(int id, int level, Trainer *ptr_to_trainer);
    GladiatorID(int id, int level);
    GladiatorID(const GladiatorID &gladiatorID);
    ~GladiatorID() {};
    int getID() const;
    int getLevel() const;
    void setTrainerPtr(Trainer *trainer);
    Trainer* getTrainerPtr() const;
    bool operator<(const GladiatorID &gladiator2) const;
    bool operator>(const GladiatorID &gladiator2) const;
};

bool operator==(const GladiatorID &gladiator1, const GladiatorID &gladiator2);
bool operator!=(const GladiatorID &gladiator1, const GladiatorID &gladiator2);


#endif //WET1_GLADIATORID_H
