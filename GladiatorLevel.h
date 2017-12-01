//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATORLEVEL_H
#define WET1_GLADIATORLEVEL_H

#include "Gladiator.h"

class GladiatorLevel : public Gladiator {
public:
    GladiatorLevel(int id, int level);
    ~GladiatorLevel() {};
    int GetID();
    bool operator<(const Gladiator &gladiator2) const;
    bool operator>(const Gladiator &gladiator2) const;
};



#endif //WET1_GLADIATORLEVEL_H
