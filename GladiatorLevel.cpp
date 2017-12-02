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

GladiatorLevel::GladiatorLevel(int id, int level) : Gladiator(id, level) {}

GladiatorLevel :: GladiatorLevel(const GladiatorLevel& gladiator) : Gladiator(gladiator.level, gladiator.id){}

int GladiatorLevel::getLevel() const {
    return Gladiator::getLevel();
}

int GladiatorLevel::getID() const {
    return Gladiator::getID();
}
