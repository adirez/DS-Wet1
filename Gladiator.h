//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATOR_H
#define WET1_GLADIATOR_H

#include "SplayTree.h"
#include "Colosseum.h"
#include "Trainer.h"

class Gladiator{
public:
    Gladiator(int id, int level);
    virtual ~Gladiator() {};
    int getID() const;

protected:
    friend class Stimulant;
    friend class Colosseum;
    int id;
    int level;
    virtual bool operator<(const Gladiator &gladiator2) const = 0;
    virtual bool operator>(const Gladiator &gladiator2) const = 0;
    bool operator==(const Gladiator &gladiator2) const;
    bool operator!=(const Gladiator &gladiator2) const;
};

class GladiatorID : public Gladiator{
private:
    friend class Colosseum;
    Trainer *ptr_to_trainer;
public:
    GladiatorID(int id, int level, Trainer *ptr_to_trainer);
    GladiatorID(int id, int level);
    ~GladiatorID() {};
    int GetID();
    bool operator<(const Gladiator &gladiator2) const;
    bool operator>(const Gladiator &gladiator2) const;
};

class GladiatorLevel : public Gladiator{
public:
    GladiatorLevel(int id, int level);
    ~GladiatorLevel() {};
    int GetID();
    bool operator<(const Gladiator &gladiator2) const;
    bool operator>(const Gladiator &gladiator2) const;
};


#endif //WET1_GLADIATOR_H
