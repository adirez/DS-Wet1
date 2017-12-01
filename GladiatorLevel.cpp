//
// Created by adire on 01-Dec-17.
//

#include "GladiatorLevel.h"

bool GladiatorLevel::operator<(const Gladiator &gladiator2) const {
    if(level < gladiator2.getLevel()) return true;
    if(level == gladiator2.getLevel()){
        return id > gladiator2.getID();
    }
    return false;
}

bool GladiatorLevel::operator>(const Gladiator &gladiator2) const {
    if(level > gladiator2.getLevel()) return true;
    if(level == gladiator2.getLevel()){
        return id < gladiator2.getID();
    }
    return false;
}

int GladiatorLevel :: GetID() {
    return Gladiator :: getID();
}

int GladiatorLevel :: GetLevel() {
    return Gladiator :: getLevel();
}

GladiatorLevel::GladiatorLevel(int id, int level) : Gladiator(id, level) {}