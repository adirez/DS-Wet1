//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATORID_H
#define WET1_GLADIATORID_H

#include "Trainer.h"
#include "GladiatorLevel.h"

class GladiatorID : public GladiatorLevel{
private:
    Trainer *trainer_ptr;

public:
    GladiatorID();
    GladiatorID(int id, int level, Trainer *ptr_to_trainer);
    GladiatorID(int id, int level);
    GladiatorID(const GladiatorID &gladiatorID);
    ~GladiatorID() {};
    void setTrainerPtr(Trainer *trainer);
    Trainer* getTrainerPtr() const;
    bool operator<(const GladiatorID &gladiator2) const;
    bool operator>(const GladiatorID &gladiator2) const;
};

#endif //WET1_GLADIATORID_H
