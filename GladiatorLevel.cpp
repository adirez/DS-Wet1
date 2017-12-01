//
// Created by adire on 01-Dec-17.
//

#include "GladiatorLevel.h"

bool GladiatorLevel::operator<(const Gladiator &gladiator2) const {
    if(getLevel() < gladiator2.getLevel()) return true;
    if(getLevel() == gladiator2.getLevel()){
        return getID() > gladiator2.getID();
    }
    return false;
}

bool GladiatorLevel::operator>(const Gladiator &gladiator2) const {
    if(getLevel() > gladiator2.getLevel()) return true;
    if(getLevel() == gladiator2.getLevel()){
        return getID() < gladiator2.getID();
    }
    return false;
}

GladiatorLevel::GladiatorLevel(int id, int level) : Gladiator(id, level) {}

int GladiatorLevel::getLevel() const {
    return Gladiator::getLevel();
}

int GladiatorLevel::getID() const {
    return Gladiator::getID();
}
